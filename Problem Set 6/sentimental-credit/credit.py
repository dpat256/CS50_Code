def main():
    cc = get_num()
    print(validate(cc))


def get_num():
    while True:
        cc = input("CC Number: ")
        if len(cc) >= 13 and len(cc) < 17 and cc.isnumeric():
            return cc
        else:
            print("Invalid CC Number")
    

def validate(cc):
    if len(cc) == 13:
        if cc[0] == '4':
            if checksum(cc):
                return "VISA"
            else:
                return "INVALID"
        else:
            return "INVALID"
    elif len(cc) == 15:
        if cc[0:2] == '34' or cc[0:2] == '37':
            if checksum(cc):
                return "AMEX"
            else:
                return "INVALID"
        else:
            return "INVALID"
    elif len(cc) == 16:
        if cc[0] == '4':
            if checksum(cc):
                return "VISA"
            else:
                "INVALID"
        elif int(cc[0:2]) >= 51 and int(cc[0:2]) <= 55:
            if checksum(cc):
                return "MASTERCARD"
            else:
                return "INVALID"
        else:
            return "INVALID"
    else:
        return "INVALID"


def checksum(cc):
    sum = 0
    multSum = 0
    flip = True
    
    for i in range(0, len(cc), -1):
        if flip:
            sum += int(cc[i])
        else:
            multSum += int(cc[i]) * 2
        flip = not flip
    
    if (sum + multSum) % 10 == 0:
        return True
    else:
        return False


main()