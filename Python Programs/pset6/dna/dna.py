import sys
import re
import csv

# Variables used in some loops 
# dna_count is where the str's are stored
dna_count = [0, 0, 0]
counter = 0
temp = 0

# Checks for the command line arguments
if (len(sys.argv) != 3):
    print("Please insert two command line arguments only")
    exit(1)

# assign the command line arguments to variables
file_csv_path = sys.argv[1]
file_dna_path = sys.argv[2]

# Open the file and check if it opened correctly
csv_file = open(file_csv_path, 'r')
dna = open(file_dna_path, 'r')
if (csv_file.mode != 'r' or dna.mode != 'r'):
    exit(2)

# Read the files in memory
csv_contents = list(csv.reader(csv_file, delimiter=','))
dna_contents = dna.read()

dna_name = csv_contents[0]
del dna_name[0]

# Close the files
csv_file.close()
dna.close()

# Stores how many columns the csv contains
colunms = len(csv_contents[0])

# Loops through dna_contents and check for the longest run for each STR
for j in range(0, colunms):
    for i in range(0, len(dna_contents), 1):
        if (dna_name[j][0] == dna_contents[i]): 
            while (True):
                if (dna_contents[i: i + len(dna_name[j])] == dna_name[j]):
                    counter += 1
                    if (temp < counter):
                        temp = counter
                    i += len(dna_name[j])    
                    continue
                else:
                    counter = 0
                    break
    if (j < 3):                
        dna_count[j] = temp 
        temp = 0
    else:
        dna_count.append(temp)
        temp = 0

# Variable used in the match loop (right below)    
match = 0

# Iterates through csv to see if there is any match 
# If the match is found just print the name and exit
for i in range(1, len(csv_contents)):
    if (int(csv_contents[i][1]) == dna_count[0]):
        temp = 1
        counter = 1
        for j in range(2, colunms + 1):
            if (csv_contents[0][j - 1] == dna_name[counter]):
                if (int(csv_contents[i][j]) == dna_count[counter]):
                    counter += 1
                    temp += 1
            if (temp == colunms):
                temp = 0
                match = i
                break
    if (match == i):
        print(csv_contents[match][0])
        exit(0)

# If no match found print No match
print("No match")