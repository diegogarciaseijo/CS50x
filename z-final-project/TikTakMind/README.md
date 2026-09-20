# TikTakMind

#### Video Demo: https://youtu.be/a4Wqia1ZdCI

#### Description:

This project is a command-line implementation of the classic game Tic-Tac-Toe, written in Python. The player competes against a computer-controlled opponent that uses the Minimax algorithm to choose its moves. The goal of the project was to create a complete game while applying programming concepts such as functions, lists, loops, conditionals, recursion, and algorithmic decision-making.

The game board is represented using a Python list containing nine positions, corresponding to the nine cells of a Tic-Tac-Toe board. An empty cell is represented by `None`, while the player and computer are represented by `O` and `X`, respectively. The program displays the board in a 3-by-3 format and, when asking the player for a move, replaces empty cells with their corresponding numbers from 1 to 9. This makes it easy for the player to identify which cell they want to select.

The `create_board` function creates a new empty board. The `show_board` function is responsible for displaying the board in the terminal. It iterates through the three rows and formats the values using vertical and horizontal separators. The `ask_for_move` function handles input from the player. It also deals with invalid input, such as entering something that is not a number or entering a number outside the range from 1 to 9. After a valid number is entered, the function converts it from the human-friendly range of 1–9 to the corresponding zero-based index used by Python lists.

The `is_valid_move` function checks whether a selected position is within the board and whether the corresponding cell is empty. This prevents the player from placing a symbol on a cell that is already occupied. The `check_for_win` function checks all eight possible winning combinations: the three rows, the three columns, and the two diagonals. If one of these combinations contains three identical non-empty symbols, the function returns the winning symbol. Otherwise, it returns `None`. The `check_for_tie` function determines whether all nine cells are occupied without requiring a winner.

At the beginning of each game, the `choose_who_starts` function randomly chooses whether the player or the computer starts. This prevents the game from always beginning in the same way and gives both possibilities an equal chance.

The main part of the computer's decision-making is the `minimax` function. Minimax is a recursive algorithm commonly used for decision-making in two-player games. In this project, `X` represents the computer and `O` represents the player. A position in which `X` has won receives a score of `1`, a position in which `O` has won receives a score of `-1`, and a tie receives a score of `0`.

For every possible move, `minimax` creates a copy of the board rather than modifying the original board. It places the current player's symbol in the selected position and recursively evaluates the resulting position from the perspective of the other player. When it is `X`'s turn, the algorithm chooses the highest possible score because the computer wants to maximize its chances of winning. When it is `O`'s turn, it chooses the lowest possible score because the player is treated as an opponent who is trying to minimize the computer's score. This process continues until the algorithm reaches a terminal position where somebody has won or the game has ended in a tie.

The `choose_ai_move` function uses `minimax` to determine the computer's actual move. It considers every currently available cell, temporarily places an `X` there, and calls `minimax` to evaluate the resulting position. The move with the highest score is selected. Because Tic-Tac-Toe has a relatively small number of possible game states, this implementation can examine the possible future moves without needing more advanced optimizations.

One design choice was to use a separate copy of the board for every hypothetical move made by Minimax. This avoids modifying the actual game board while the algorithm is evaluating possible futures. Another design choice was to keep the board as a simple list instead of using a more complicated data structure. A nine-element list is sufficient for Tic-Tac-Toe and makes checking and modifying individual cells straightforward.

The `main` function brings all of these components together. It creates the board, determines who starts, repeatedly asks the appropriate player for a move, displays the updated board, and checks whether the game has ended. The loop stops when either player wins or when all cells are occupied and the game is a tie.

I tested the program by playing against the computer and checking that it blocks winning opportunities and takes winning opportunities when they are available. I also tested the Minimax implementation by having two AI players play against each other. With both sides making optimal decisions, the games consistently ended in ties, which is the expected result for Tic-Tac-Toe when both players play perfectly.