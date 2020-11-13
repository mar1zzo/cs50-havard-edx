# program that computes the approximate grade level needed to comprehend some text

from cs50 import get_string

# Request user text
text = get_string("Text: ")

# Accountant declaration
count_letters = 0
count_text = 0
count_words = 0
count_sentences = 0

# counting the text
for i in text:
    count_text += 1

for i in range(count_text):
    # calculate of the function of counting only letters
    # using ord() --> https://docs.python.org/pt-br/3.7/library/functions.html?highlight=ord#ord
    if (ord(text[i]) >= 65 and ord(text[i]) <= 122):
        count_letters += 1

    # calculate of the function of counting only words
    elif (ord(text[i]) == 32 and (ord(text[i - 1]) != 33 and ord(text[i - 1]) != 46 and ord(text[i - 1]) != 63)):
        count_words += 1

    # calculate of the function of counting only sentences
    elif (ord(text[i]) == 33 or ord(text[i]) == 46 or ord(text[i]) == 63):
        count_sentences += 1
        count_words += 1

# Average number of letters and sentences per 100 words
l = count_letters / count_words * 100
s = count_sentences / count_words * 100

# Calculating Coleman-Liau
index = round(0.0588 * l - 0.296 * s - 15.8)

# Finally outputs the result to the user
if (index < 1):
    print("Before Grade 1")

elif (index >= 16):
    print("Grade 16+")

else:
    print(f"Grade {index}")