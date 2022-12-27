from cs50 import get_string
import re


def main():
    # Get input
    input = get_string("Text:")

    # Calculate statistics about input
    letters = len(re.findall("[a-z]|[A-Z]", input))
    words = input.count(" ") + 1
    sentences = len(re.findall("\!|\?|\.", input))
    lettersPer100Word = (letters / words) * 100
    sentencesPer100Word = (sentences / words) * 100

    # Coleman-Liau formula
    level = 0.0588 * lettersPer100Word - 0.296 * sentencesPer100Word - 15.8

    # Conform to specifications and get ready to print output
    if level >= 16:
        level = "Grade 16+"
    elif level <= 1:
        level = "Before Grade 1"
    else:
        level = "Grade " + str(round(level))
    print(level)


main()

