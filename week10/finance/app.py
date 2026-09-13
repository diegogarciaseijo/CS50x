import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute(
        "SELECT * FROM portfolio WHERE user_id = ?", session["user_id"]
    )
    cash = db.execute(
        "SELECT cash FROM users WHERE id = ?", session["user_id"]
    )[0]["cash"]
    total = cash

    for stock in rows:
        info = lookup(stock["symbol"])
        stock["individualvalue"] = info["price"]
        stock["totalvalue"] = info["price"] * stock["shares"]
        total += stock["totalvalue"]

    return render_template("index.html", stocks=rows, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        info = lookup(symbol)

        if info is None:
            return apology("that symbol does not exist", 400)

        shares = request.form.get("shares")

        if shares is None:
            return apology(
                "you need to specify an amount of shares to buy", 400
            )

        if not shares.isdigit():
            return apology(
                "you can only buy a positive whole number of shares", 400
            )

        shares = int(shares)

        if shares == 0:
            return apology("you can't buy 0 shares", 400)

        cost = info["price"] * shares
        rows = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )
        usermoney = rows[0]["cash"]

        if usermoney < cost:
            return apology("you don't have enough money", 400)
        else:
            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?",
                usermoney - cost,
                session["user_id"],
            )
            db.execute(
                "INSERT INTO transactions "
                "(user_id, symbol, shares, price, transaction_type) "
                "VALUES (?, ?, ?, ?, 'buy')",
                session["user_id"],
                symbol,
                shares,
                info["price"],
            )

            # Check if the user already has shares from that company
            rows = db.execute(
                "SELECT shares FROM portfolio "
                "WHERE user_id = ? AND symbol = ?",
                session["user_id"],
                symbol,
            )

            if rows:
                db.execute(
                    "UPDATE portfolio SET shares = ? "
                    "WHERE user_id = ? AND symbol = ?",
                    shares + rows[0]["shares"],
                    session["user_id"],
                    symbol,
                )
            else:
                db.execute(
                    "INSERT INTO portfolio (user_id, symbol, shares) "
                    "VALUES (?, ?, ?)",
                    session["user_id"],
                    symbol,
                    shares,
                )

            return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute(
        "SELECT * FROM transactions WHERE user_id = ?", session["user_id"]
    )
    return render_template("history.html", transactions=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        info = lookup(symbol)

        if info is None:
            return apology("that symbol does not exist", 400)
        else:
            return render_template(
                "quoted.html",
                name=info["name"],
                value=info["price"],
                symbol=info["symbol"],
            )
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password was confirmed
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        # Ensure password and confirmation match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Check if that username is already in use
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        if len(rows) > 0:
            return apology("that username is already in use")

        # If every check works the user is registered
        else:
            name = request.form.get("username")
            password_hash = generate_password_hash(
                request.form.get("password")
            )
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)",
                name,
                password_hash,
            )
            return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        info = lookup(symbol)

        if info is None:
            return apology("that symbol does not exist", 400)

        shares = request.form.get("shares")

        if shares is None:
            return apology(
                "you need to specify an amount of shares to sell", 400
            )

        if not shares.isdigit():
            return apology(
                "you can only sell a positive whole number of shares", 400
            )

        shares = int(shares)

        if shares == 0:
            return apology("you can't sell 0 shares", 400)

        cost = info["price"] * shares
        rows = db.execute(
            "SELECT shares FROM portfolio "
            "WHERE user_id = ? AND symbol = ?",
            session["user_id"],
            symbol,
        )

        if not rows:
            return apology("you don't have shares from that company")

        usershares = rows[0]["shares"]

        if usershares < shares:
            return apology("you don't have enough shares to sell", 400)
        else:
            db.execute(
                "UPDATE portfolio SET shares = ? "
                "WHERE user_id = ? AND symbol = ?",
                usershares - shares,
                session["user_id"],
                symbol,
            )
            rows = db.execute(
                "SELECT cash FROM users WHERE id = ?", session["user_id"]
            )
            usercash = rows[0]["cash"]

            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?",
                usercash + cost,
                session["user_id"],
            )
            db.execute(
                "INSERT INTO transactions "
                "(user_id, symbol, shares, price, transaction_type) "
                "VALUES (?, ?, ?, ?, 'sell')",
                session["user_id"],
                symbol,
                shares,
                info["price"],
            )

        if usershares - shares == 0:
            db.execute(
                "DELETE FROM portfolio WHERE user_id = ? AND shares = 0",
                session["user_id"],
            )

        return redirect("/")

    else:
        rows = db.execute(
            "SELECT * FROM portfolio WHERE user_id = ?", session["user_id"]
        )
        return render_template("sell.html", stocks=rows)
