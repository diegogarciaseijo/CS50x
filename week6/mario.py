from cs50 import get_int

# Getting the height from the user and checking that it is between 1 and 8
height = get_int("Height: ")
while (height <= 0 or height >= 9):
    height = get_int("Height: ")

# Printing the pyramid of the height given by the user
for row in range(height):
    for column in range(height - row - 1):
        print(" ", end="")
    for column in range(row + 1):
        print("#", end="")
    print("  ", end="")
    for column in range(row + 1):
        print("#", end="")
    print("")
