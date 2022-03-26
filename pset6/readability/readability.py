import cs50


def main():

    s = cs50.get_string("Text: ")

    chars = len(s)
    words = 1
    sentences = 0

    for string_check in s:
        if (ord(string_check) < 65 or ord(string_check) > 90) and (ord(string_check) < 97 or ord(string_check) > 122):
            chars -= 1

        if string_check == " ":
            words += 1

        if string_check == "." or string_check == "!" or string_check == "?":
            sentences += 1

    print(f"c: {chars} w: {words} s: {sentences}")

    L = (100 / words) * chars
    S = (100 / words) * sentences
    coleman = round(0.0588 * L - 0.296 * S - 15.8)

    if coleman < 1:
        print("Before Grade 1")
    elif coleman > 16:
        print("Grade 16+")
    else:
        print(f"Grade {coleman}")


if __name__ == "__main__":
    main()