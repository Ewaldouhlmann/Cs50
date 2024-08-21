from cs50 import get_int


def main():
    card_num = get_int("Type the card number: ")
    if valid_luhn_card(card_num):
        get_card_type(card_num)
    else:
        print("INVALID")


def get_card_type(number):
    if int(number / 100000000000000) <= 55 and int(number / 100000000000000) > 50:
        print("MASTERCARD")
    elif int(number/1000000000000000) == 4 or int(number/1000000000000) == 4:
        print("VISA")
    elif int(number/10000000000000) == 34 or int(number/10000000000000) == 37:
        print("AMEX")
    else:
        print("INVALID")


def valid_luhn_card(card):
    sum = 0
    while (card > 0):
        last_digit = int(card % 10)
        card = int(card/10)
        dup_penult = int(card % 10) * 2
        if dup_penult > 9:
            firs_char = int(dup_penult % 10)
            dup_penult = int(dup_penult / 10)
            sum += dup_penult + firs_char
        else:
            sum += dup_penult
        sum += last_digit
        card = int(card / 10)
    if sum % 10 == 0:
        return True
    return False


main()
