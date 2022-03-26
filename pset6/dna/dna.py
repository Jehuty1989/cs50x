import csv
from sys import argv

# 2 global variables
current_STR = 1
match_found = False


def main():
    if len(argv) != 3:
        print("Missing/incorrect command-line argument(s)")
        return 1

    # with open func to read the file to the end
    with open(argv[1], "r") as database:
        # I start by using a csv.reader and not csv.DictReader as I want access to the first line of the file
        header_reader = csv.reader(database)
        # Store the dna sequences as a set of strings
        for STR in header_reader:
            # Remove the first string as it is "name" and I do not need that
            STR.pop(0)
            break

        # Scroll back to the beginning of the file
        database.seek(0)

        # Create a blank list
        data = []

        data_reader = csv.DictReader(database)
        for row in data_reader:
            # Fill the list with dictionaries
            # I now have a list of dictionaries which I can index into with an int and a key
            data.append(row)

    # Create a blank library
    STR_LIB = {}

    for x in range((len(STR))):
        # I then set all the values in the library to 0
        STR_LIB[(STR[x])] = 0

    # Put the dna sequence into memory
    with open(argv[2], "r") as sequence_file:
        for sequence in sequence_file:
            # A simple way to write the first line of a file into memory using a for in argument
            # A for in argument requires a command and pass does nothing. I use it to stop the interpreter from stopping at this point
            pass

    seq_search(sequence, STR, STR_LIB)

    for x in range(len(data)):
        find_match(x, STR, STR_LIB, data)

    global match_found

    # This is just to check if a match was found
    if match_found == False:
        print("No match")


def seq_search(sequence, STR, STR_LIB):
    # If you use a global variable it must be declared like this.
    global current_STR

    # Variable to keep track of search and not go over
    x = 0

    while True:
        # I do not know of a way to change the y variable so once a repeating sequence is found the for in will carry on finding the specific sequence - 1 until there are no more
        # I put a simple if check in back_to_back to stop this
        for y in range(len(sequence) + 1):
            z = len(STR[x])
            if STR[x] in sequence[y:(y + z)]:
                # If a match is found back_to_back is used to see if there is a repeating sequence of them
                back_to_back(x, y, z, sequence, STR, STR_LIB)

        # This will move to the next person on the STR
        x += 1
        # Reset current_STR
        current_STR = 1
        # This check will end the while loop before there is an error because x is too high to index into STR
        if x > len(STR) - 1:
            break


def back_to_back(x, y, z, sequence, STR, STR_LIB):
    global current_STR

    # This is to check if back_to_back is checking the same repeating sequence of dna
    # If it is it will simply return
    if current_STR > 1:
        return

    while True:
        # If the programme is here there is at least one sequence
        # This will check to see if the same sequence following it
        if STR[x] == sequence[(y + z):(y + z + z)]:
            # This is to move the search area
            y = y + z
            current_STR += 1
        else:
            # Only update if the current chain is higher than what is stored in STR_LIB
            if current_STR > STR_LIB[(STR[x])]:
                STR_LIB[(STR[x])] = current_STR
                current_STR = 1
                break
            break


def find_match(x, STR, STR_LIB, data):
    global match_found

    for y in range(len(STR_LIB)):
        # This will check to see if how many repeating dna sequences match any of the records
        # Cast the values in data dictionary to integers as they are stored as strings
        if STR_LIB[(STR[y])] == int(data[x][STR[y]]):
            # The only way y will equal (len(STR) - 1) is if the amount of repeating dna sequences matches all the values in the data dictionary
            # for any given person. Therefore it is safe to assume that this will be the only match
            if y == (len(STR) - 1):
                print(f"{data[x]['name']}")
                # Change the value of match_found bool to True
                match_found = True
        else:
            break


if __name__ == "__main__":
    main()