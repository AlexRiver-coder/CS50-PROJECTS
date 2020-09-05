import sys
from cs50 import SQL
import csv

# Checks for the correct number of command line
if (len(sys.argv) != 2):
    print("Please insert only two command line arguments")
    exit(1)
    
# Stores the house input in the variable
house_name = sys.argv[1]

# Open data bank
db = SQL("sqlite:///students.db")

# Querry for the first , middle and last nime + birth for each person who lives in the same location
for row in db.execute("SELECT first, middle, last, birth FROM students WHERE house = '%s' ORDER BY last, first" %house_name):
    if (row['middle'] == 'NULL'):
        print(f"{row['first']} {row['last']}, born {row['birth']}")
        continue
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
        
        



