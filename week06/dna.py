# NOTE: The main function was written by me.
# The longest_match function was provided by CS50.

import csv
import sys


def main():

    # Check for command-line usage
    if (len(sys.argv) != 3):
        print("Wrong usage")
        sys.exit()

    # Read database file into a variable
    people = []
    with open(sys.argv[1], 'r') as database:
        reader = csv.DictReader(database)
        for row in reader:
            people.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as sequence:
        dna = sequence.read()

    # Find longest match of each STR in DNA sequence
    str_counts = {}
    for key in people[0].keys():
        if (key != "name"):
            str_counts[key] = longest_match(dna, key)

    # Check database for matching profiles
    for person in people:
        match = True
        for key in str_counts:
            if (int(person[key]) != str_counts[key]):
                match = False
        if match:
            print(person["name"])
            sys.exit()
    print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
