# Prompts the user for the text and get the text length
text = input("Text: ")
text_len = len(text)

# Variables used to count words, sentences and letters
# Words start at 1 because the for loop does not count the last word since there's no space after it
words = 1
sentences = 0
setence_list = [".", "?", "!"]
letters = 0
index = 0

# Loop through the text collecting quantity of words, sentences and letters
for i in range(text_len):
    if (text[i] == " "):
        words += 1
    if (text[i] in setence_list):
        sentences += 1
    if (str.isalpha(text[i])):
        letters += 1

# implement Coleman-Liau index 
index = 0.0588 * (100 * letters / words) - 0.296 * (100 * sentences / words) - 15.8
index = round(index)

# Checks for the user's grade
if (index >= 16):
    print("Grade 16+")
elif (index < 1):
    print("Before Grade 1")
else:
    print(f"Grade {index}")