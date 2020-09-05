from sys import exit
import math

# Lists containing the possible first digits of each brand
# Except for visa var, it contains the possible digits length
amex = [34, 37]
master = [55, 52, 53, 54, 51]
visa = [13, 16]

# Get user's input and set some variables related to the card
card_number = input("Number: ")
card_len = len(card_number)
sum = 0
card_firstdgts = 0
helper = 0

# For loop to do Luhn's algorithm and to get the first card digits
for i in range((card_len - 1), -1, -1):
    if (helper == 1 or helper % 2 != 0):
        temp = int(card_number[i]) * 2
        if (temp >= 10):
            temp2 = temp % 10
            sum += temp2 + math.floor(temp / 10)
        else:
            sum += int(card_number[i]) * 2
        helper += 1    
        continue
    else:
        sum += int(card_number[i])
        helper += 1

# Loop to get the first two numbers of the card
card_firstdgts = int(card_number)
while True:
    card_firstdgts = card_firstdgts / 10
    if (card_firstdgts < 100):
        card_firstdgts = math.floor(card_firstdgts)
        break

# Checks to see if the card is legit or not        
if (sum % 10 != 0):
    print("INVALID")
    exit(1)

# Checks to see if the quantity of digits matches with any card
if (card_len == 15 and card_firstdgts in amex):
    print("AMEX")
    exit(0)
elif (card_len == 16 and card_firstdgts in master):
    print("MASTERCARD")
    exit(0)
elif (card_len in visa and math.floor(card_firstdgts / 10) == 4):
    print("VISA")
    exit(0)
else:
    print("INVALID")
    exit(1)