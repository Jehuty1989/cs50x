import cs50


def main():

    amex, mc, visa, z = 0, 0, 0, 0

    x = cs50.get_int("Number: ")

    if (x > 3999999999999999 and x < 5000000000000000) or (x > 3999999999999 and x < 5000000000000):
        visa = 1

        z = get_luhn(x)

    elif (x > 339999999999999 and x < 350000000000000) or (x > 369999999999999 and x < 380000000000000):
        amex = 1

        z = get_luhn(x)

    elif (x > 5099999999999999 and x < 5600000000000000):
        mc = 1

        z = get_luhn(x)

    if (visa == 1 and z == 0):
        print("VISA")

    elif (amex == 1 and z == 0):
        print("AMEX")

    elif (mc == 1 and z == 0):
        print("MASTERCARD")

    else:
        print("INVALID")


def get_luhn(x):

    a = x % 10
    b = int((x / 10) % 10) * 2
    c = int(x / 100) % 10
    d = int((x / 1000) % 10) * 2
    e = int(x / 10000) % 10
    f = int((x / 100000) % 10) * 2
    g = int(x / 1000000) % 10
    h = int((x / 10000000) % 10) * 2
    i = int(x / 100000000) % 10
    j = int((x / 1000000000) % 10) * 2
    k = int(x / 10000000000) % 10
    l = int((x / 100000000000) % 10) * 2
    m = int(x / 1000000000000) % 10
    n = int((x / 10000000000000) % 10) * 2
    o = int(x / 100000000000000) % 10
    p = int((x / 1000000000000000) % 10) * 2

    if (b > 9):
        b = b - 9

    if (d > 9):
        d = d - 9

    if (f > 9):
        f = f - 9

    if (h > 9):
        h = h - 9

    if (j > 9):
        j = j - 9

    if (l > 9):
        l = l - 9

    if (n > 9):
        n = n - 9

    if (p > 9):
        p = p - 9

    luhn = (a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p) % 10

    return luhn


if __name__ == "__main__":
    main()