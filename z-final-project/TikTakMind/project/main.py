# AI tool used: ChatGPT and GitHub Copilot
# Used as helpers for debugging, explaining concepts, and reviewing code

import random


# All possible winning combinations of cells on the board
WINNING_COMBINATIONS = [
    (0, 1, 2),
    (3, 4, 5),
    (6, 7, 8),
    (0, 3, 6),
    (1, 4, 7),
    (2, 5, 8),
    (0, 4, 8),
    (2, 4, 6),
]


def create_board():
    return [None] * 9


def show_board(board):
    for row in range(3):
        start = row * 3
        values = [
            " " if value is None else str(value)
            for value in board[start:start + 3]
        ]

        print(f" {values[0]} | {values[1]} | {values[2]} ")

        if row < 2:
            print("---|---|---")


def ask_for_move(board):
    board_with_numbers = [
        position + 1 if value is None else value
        for position, value in enumerate(board)
    ]

    show_board(board_with_numbers)

    while True:
        try:
            choice = int(input("Choose a cell from 1 to 9: "))
        except ValueError:
            print("Enter a number from 1 to 9")
            continue

        if 1 <= choice <= 9:
            return choice - 1

        print("The number must be between 1 and 9")


def is_valid_move(move, board):
    return 0 <= move < len(board) and board[move] is None


def check_for_win(board):
    for first, second, third in WINNING_COMBINATIONS:
        if board[first] is not None and board[first] == board[second] == board[third]:
            return board[first]

    return None


def check_for_tie(board):
    return all(value is not None for value in board)


def choose_who_starts():
    return random.choice(["player", "computer"])


def minimax(board, turn):
    winner = check_for_win(board)

    # Terminal positions are scored from the computer's perspective
    if winner == "X":
        return 1

    if winner == "O":
        return -1

    if check_for_tie(board):
        return 0

    if turn == "X":
        best_score = -1
    else:
        best_score = 1

    for move in range(len(board)):
        if not is_valid_move(move, board):
            continue

        board_copy = board.copy()
        board_copy[move] = turn

        # Recursively evaluate the position after this move
        next_turn = "O" if turn == "X" else "X"
        score = minimax(board_copy, next_turn)

        # X maximizes the score, while O minimizes it
        if turn == "X":
            best_score = max(best_score, score)
        else:
            best_score = min(best_score, score)

    return best_score


def choose_ai_move(board):
    best_score = -1
    best_move = None

    # Evaluate every possible move and choose the one with the best outcome
    for move in range(len(board)):
        if not is_valid_move(move, board):
            continue

        board_copy = board.copy()
        board_copy[move] = "X"

        score = minimax(board_copy, "O")

        if score > best_score:
            best_score = score
            best_move = move

    return best_move


def main():
    board = create_board()
    turn = choose_who_starts()

    print(f"{turn.capitalize()} starts")

    while True:
        if turn == "player":
            move = ask_for_move(board)

            while not is_valid_move(move, board):
                print("That cell is already occupied")
                move = ask_for_move(board)

            board[move] = "O"
            next_turn = "computer"

        else:
            move = choose_ai_move(board)
            board[move] = "X"

            print(f"Computer chose cell {move + 1}")

            next_turn = "player"

        show_board(board)

        winner = check_for_win(board)

        if winner is not None:
            if winner == "O":
                print("You win!")
            else:
                print("Computer wins!")

            break

        if check_for_tie(board):
            print("It's a tie!")
            break

        turn = next_turn


if __name__ == "__main__":
    main()