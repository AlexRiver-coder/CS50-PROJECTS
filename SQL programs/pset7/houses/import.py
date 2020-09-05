import sys
from cs50 import SQL
import csv

# Checks for the correct number of command line
if (len(sys.argv) != 2):
    print("Please insert only two command line arguments")
    exit(1)

# Opening file for SQLite
db = SQL("sqlite:///students.db")

# Storing file name from user
csv_name = sys.argv[1]
csv_file = open(csv_name, 'r')

if (csv_file.mode != 'r'):
    exit(2)

# Read file in the memory
csv_contents = list(csv.reader(csv_file, delimiter='\t'))

# Iterates through all the lines in the 'file'
# Get the firs name, middle and last for each student +
# Get the houses and birth too and insert into the table
for i in range(1, len(csv_contents)):
    x = 0
    check_name = 0
    house_aux = 0
    for j in range(len(csv_contents[i][0])):
        if (csv_contents[i][0][j] == " " and x == 0):
            firts_name = csv_contents[i][0][x:j]
            x = j + 1
            check_name += 1
            continue
        if (csv_contents[i][0][j] == " "):
            middle_name = csv_contents[i][0][x:j]
            x = j + 1
            check_name += 1
            continue
        if (csv_contents[i][0][j] == ","):
            last_name = csv_contents[i][0][x:j]
            for l in range(j + 1, len(csv_contents[i][0])):
                if (csv_contents[i][0][l] == ","):
                    house = csv_contents[i][0][j + 1:l]
                    birth = csv_contents[i][0][l + 1:]
                    break
            break
    if (check_name == 1):
        middle_name = "NULL"
    db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", firts_name, middle_name, last_name, house, int(birth))
    
# Close files opened
csv_file.close()

    