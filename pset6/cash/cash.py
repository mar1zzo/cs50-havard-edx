# program that calculates the minimum number of coins required to give a user change

from cs50 import get_float

# requests a currency amount
value = 0
while (value <= 0):
    value = get_float("Change owed: ")

# initializing the variables
count = 0
coins = round(value * 100, 0)

# counting the coins
while (coins > 0):
    if (coins >= 25):
        coins -= 25
        count += 1
    elif (coins >= 10):
        coins -= 10
        coins += 1
    elif (coins >= 5):
        coins -= 5
        count += 1
    else:
        coins -= 1
        count += 1

# presents the change to the user
print(count)