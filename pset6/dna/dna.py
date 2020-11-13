# program that identifies a person based on their DNA

from csv import reader, DictReader
from sys import argv

# checking the number of command line arguments
if len(argv) < 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# opening and reading the DNA sequences
with open(argv[2]) as file:
    file_reader = reader(file)
    for row in file_reader:
        dna_list = row

# auxiliary variable declaration
dna = dna_list[0]
sequences = {}

# opening and reading the DNA databases
with open(argv[1]) as database:
    people = reader(database)
    for row in people:
        dna_sequences = row
        # excluding csv header
        # use --> array.pop in https://docs.python.org/pt-br/3.7/library/array.html?highlight=pop
        dna_sequences.pop(0)
        break

# copies only the AGAT gene
for i in dna_sequences:
    sequences[i] = 1

# count the repetitions
for STR in sequences:

    temp = 0
    len_key = len(STR)
    temp_max = 0

    # eliminates already read string
    for i in range(len(dna)):
        while temp > 0:
            temp -= 1
            continue

        # account dna repetitions
        if dna[i: i + len_key] == STR:
            while dna[i - len_key: i] == dna[i: i + len_key]:
                temp += 1
                i += len_key

            # ensures that the string is the longest
            if temp > temp_max:
                temp_max = temp

    # armazena a sequencia que mais apresenta STR
    sequences[STR] += temp_max

# open the dictionary and search for the DNA sequence by name
with open(argv[1], newline='') as database:

    peoples = DictReader(database)

    for name in peoples:
        equal = 0
        # compares and prints the person's name
        for dna in sequences:
            if sequences[dna] == int(name[dna]):
                equal += 1
        if equal == len(sequences):
            print(name['name'])
            exit(0)

    # otherwise, print "no match"
    print("No match")