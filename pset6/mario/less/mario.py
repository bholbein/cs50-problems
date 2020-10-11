number = 0
while True:
    try:
        number = int(input("Please input a number between 1 and 8: "))
    except ValueError:
        continue
    else:
        if (number < 1 or number > 8):
            continue
        else:
            break

for i in range(number):
    print(" " * (number - i - 1), end="")
    print("#" * (i+1))