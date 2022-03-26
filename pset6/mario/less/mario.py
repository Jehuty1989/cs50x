import cs50

# Infinite while loop
while True:
    # "cs50.get_int" will handle any non integer inputs
    x = cs50.get_int("Height: ")
    # This will check to see if x is larger than 0 and smaller than 9
    # If it is, break the loop
    if x > 0 and x < 9:
        break

# New variable to be used in spacing and "#" printing
y = x - 1

for z in range(0, x, 1):
    # "print" can run multiple times in an instance using "* int"
    # "print" always ends with a new-line so "end=""" will add nothing
    # to the end of the "print" function as opposed to a new-line
    print(" " * y, end="")
    print("#" * (x - y), end="")
    # This blank "print" will add a new-line
    print("")
    y -= 1