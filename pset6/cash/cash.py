# constants
coins = [0.25, 0.1, 0.05, 0.01]

def main():
    print(round(calc_change(get_input(), coins)))

def get_input():
    """Return positive float number as valid user input"""    
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


def calc_change(cash: float, coins: list):
    """Returns minimal number of coins for change"""
    counter = 0
    for i in coins:
        counter = counter + (cash // i)
        cash = round(cash % i, 2)
        if cash == 0:
            break
    return counter

main()