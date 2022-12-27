from cs50 import get_int


def main():
    height = 0
    # Get height input from user, repeating until valid
    while height < 1 or height > 8:
        height = get_int("Height: ")
    # Loop through all rows
    for row in range(1, height + 1):
        # Print first spaces to indent
        print(" " * (height - row), end="")
        # Print left hashes
        print("#" * row, end="")
        # Print space between pyramid
        print("  ", end="")
        # Print right hashes
        print("#" * row)


main()