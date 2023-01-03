while True:
    height = input("Height: ")
    try:
        height = int(height)
        if (height in range(1, 9)):
            break
        else:
            print("Invalid input.")
    except ValueError:
        print("Invalid input.")

for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i + "  " + "#"*i)