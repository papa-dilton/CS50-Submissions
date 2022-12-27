from cs50 import get_int


def main():
    # Get card input
    input = get_int("Number: ")
    card = str(input)

    ##### Implement Luhn's Algorithm #####
    sum = 0

    # Multiply every second number by 2
    digit = []
    if len(card) % 2 == 0:
        isEven = True
    else:
        isEven = False

    for i in range(len(card)):
        # Process cards with an even number of digits
        cur_num = int(card[i])
        if (i % 2 == 0 and isEven) or (i % 2 == 1 and not isEven):
            cur_num *= 2
            if cur_num > 9:
                cur_num = (cur_num % 10) + 1
        # Add whatever the odd digit or modified even digit is
        sum += cur_num

    # Detect valid card
    if sum % 10 == 0:
        length = len(card)
        # Detect digit diferences for card carrier
        if (card[0] == "4") and (length == 13 or length == 16):
            print("VISA")
        elif (card[0] == "3" and (card[1] == "4" or card[1] == "7")) and (length == 15):
            print("AMEX")
        elif (card[0] == "5" and (card[1] >= "1" and card[1] <= "5")) and (length == 16):
            print("MASTERCARD")
        else:
            print("INVALID")
    # Detect invalid card
    else:
        print("INVALID")


main()