from sys import exit


number = input("Number: ")
while (not number.isdigit()):
    print("You can only input numbers")
    number = input("Number: ")
digitsn = len(number)
digit = 0
luhn = 0

# Calculate the luhn checksum
for i in range(-2, -digitsn-1, -2):
    digit = int(number[i]) * 2
    if (digit >= 10):
        luhn = luhn + digit // 10 + digit % 10
    else:
        luhn = luhn + digit
for i in range(-1, -digitsn-1, -2):
    luhn = luhn + int(number[i])

# Determine the card issuer and print it
if (luhn % 10 != 0):
    print("INVALID")
    exit()
elif (digitsn == 15 and number[0] == "3" and (number[1] == "4" or number[1] == "7")):
    print("AMEX")
    exit()
elif (digitsn == 16 and number[0] == "5" and "1" <= number[1] <= "5"):
    print("MASTERCARD")
    exit()
elif ((digitsn == 13 or digitsn == 16) and number[0] == "4"):
    print("VISA")
    exit()
else:
    print("INVALID")
    exit()
