text = input("Text: ")
# Counting the number of letters, words and sentences
letterscount = sum(character.isalpha() for character in text)
wordscount = len(text.split())
sentencescount = text.count(".") + text.count("?") + text.count("!")

# Calculating the Coleman-Liau index
L = letterscount / wordscount * 100
S = sentencescount / wordscount * 100
index = 0.0588 * L - 0.296 * S - 15.8

# Printing the text's grade based on the index
if (index < 1):
    print("Before Grade 1")
elif (index >= 16):
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")
