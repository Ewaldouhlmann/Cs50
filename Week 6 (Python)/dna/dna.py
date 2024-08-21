import csv
import sys


def main():

    # TODO: Check for command-line usage
    # verifying if has 3 arguments in comand-line. If has, assuming that is valid files
    if len(sys.argv) != 3:
        print("Usage: python script.py database.csv sequence.txt")
        sys.exit(1)

    # storing data and keys into variables
    data, keys = read_data(sys.argv[1])

   # storing dna in a variable
    dna = get_dna(sys.argv[2])

    # TODO: Find longest match of each STR in DNA sequence
    # getting the longest match of each STR in DNA
    str_list = str_in_dna(keys, dna)

    # TODO: Check database for matching profiles
    person_match = get_person_with_dna(data, str_list)
    print(person_match)

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


def read_data(arquive):
    # this functions get the keys and the content for a file and store in a variable
    rows = []
    with open(arquive) as file:
        reader = csv.DictReader(file)
        keys = reader.fieldnames
        for row in reader:
            rows.append(row)
    return rows, keys


def get_dna(file_):
    # this functions get a file and store it in a variable
    with open(file_, 'r') as file:
        dna = file.read()
    return dna


def str_in_dna(keys, dna):
    # Geting each STR count in a dna sequence
    str_list = []
    for key in keys:
        if (key != 'name'):
            str_list.append(longest_match(dna, key))
    return str_list


def get_person_with_dna(data, str_list):
    # Scrolling through each person in the data
    for person in data:
        # Defining the current idx for a STR list and a flag to define if has match
        current_idx = 0
        person_match = True
        # Scrolling through each key by person
        for person_keys in person:
            # Checks if the current key person matches with espected value
            if (person_keys != 'name'):
                if (str_list[current_idx] != int(person[person_keys])):
                    # If not, setting curren person key to False and breaking the loop
                    person_match = False
                    break
                current_idx += 1
        # If find a person who match with current DNA, retunrs the persons name
        if (person_match == True):
            return person['name']

    # If no match is found, returns no match
    if (person_match == False):
        return "No match"


main()
