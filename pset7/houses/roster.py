# program that prints a list of students for a given house in alphabetical order.

from cs50 import SQL
from sys import argv

# If the incorrect number of command-line arguments are provided, your program should print an error and exit
if len(argv) < 2:
    print("Error, Usage: python roster.py houseName")
    exit(1)

# open the database
db = SQL("sqlite:///students.db")
# Your program should query the students table in the students.db database for all of the students in the specified house
students = db.execute("SELECT * FROM students WHERE house = (?) ORDER BY last, first", argv[1])

# Your program should then print out each student’s full name and birth year
for student in students:
    if student['middle'] != None:
        print(f"{student['first']} {student['middle']} {student['last']}, born {student['birth']}")
    else:
        print(f"{student['first']} {student['last']}, born {student['birth']}")
# successful
exit(0)