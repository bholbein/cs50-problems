# constants
coins = [0.25, 0.1, 0.05, 0.01]


def main():
    print(round(calc_change(get_input())))


def get_input():
    """Return positive float number as valid user input"""
    cash = 0.0
    while True:
        try:
            cash = float(input("Change owned: "))
        except ValueError:
            continue
        else:
            if cash <= 0:
                continue
        break
    return cash


def calc_change(cash: float):
    """Returns minimal number of coins for change"""
    counter = 0
    rest = cash
    for i in coins:
        counter = counter + (rest // i)
        rest = round(rest % i, 2)
        if rest == 0:
            break
    return counter


main()
