import csv
import sys


def main():

    # Check for proper command-line usage
    if len(sys.argv) != 3:
        sys.exit("USAGE: python dna.py database.csv dna-squence.txt")
    if not sys.argv[1].endswith(".csv") or not sys.argv[2].endswith(".txt"):
        sys.exit("Improper file format")

    # Read database file into a variable
    data = []
    with open(sys.argv[1], "r") as database:
        reader = csv.DictReader(database)
        for person in reader:
            data.append(person)

    # Read DNA sequence file into a variable
    sequence = open(sys.argv[2]).read()

    # Find longest match of each STR in DNA sequence
    unknownPerson = {"name": ""}
    segsToCheck = list(data[0].keys())[1::]
    for segment in segsToCheck:
        unknownPerson[segment] = longest_match(sequence, segment)

    # Check database for matching profiles
    for personToCheck in data:
        iterator = 0
        for key in personToCheck:
            if key != "name":
                if int(unknownPerson[key]) != int(personToCheck[key]):
                    iterator = 0
                    break
                elif iterator == len(segsToCheck) - 1:
                    print(personToCheck["name"])
                    return
                iterator += 1

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

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
