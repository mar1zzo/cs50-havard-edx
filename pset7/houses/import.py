# program that imports data from a CSV spreadsheet.

from cs50 import SQL
from csv import reader
from sys import argv

# open the database
db = SQL("sqlite:///students.db")

# If the incorrect number of command-line arguments are provided, your program should print an error and exit
if len(argv) < 2:
    print("Error, Usage: python import.py characters.csv")
    exit(1)

# open the csv file
with open(argv[1], newline='') as file:
    students = reader(file)
    # reading the file and skipping the header
    for student in students:
        if student[0] == 'name':
            continue

        # isolating the name field
        full_name = student[0].split()

        # checking that the full name has a middle name
        if len(full_name) < 3:
            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       full_name[0], None, full_name[1], student[1], student[2])
        else:
            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       full_name[0], full_name[1], full_name[2], student[1], student[2])
# successful insert
exit(0)