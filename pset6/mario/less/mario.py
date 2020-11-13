# program that prints out a half-pyramid of a specified height

from cs50 import get_int


def main():
    n = get_positive_int()
    pyramid(n)

# Prompt user for positive integer


def get_positive_int():
    while True:
        n = get_int("Height: ")
        if n > 0 and n < 9:
            break
    return n

# Print Mario's right-aligned pyramid


def pyramid(n):
    for i in range(1, n + 1):
        print(" " * (n - i), end="")
        print("#" * (i))


# call main function
main()