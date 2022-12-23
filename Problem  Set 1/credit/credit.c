#include <stdio.h>
#include <stdbool.h>

long get_num();
const char* validate(long cc);
bool checksum (long cc, int check);

int main(void) 
{
    
    long cc = get_num();
    printf("%s", validate(cc));

}

long get_num()
{
    long cc;
    printf("Enter CC Number: ");
    scanf("%ld", &cc);
    
    return cc;
}

const char* validate(long cc)
{
    long check13 = 1000000000000;
    long check14 = 10000000000000;
    long check15 = 100000000000000;
    long check16 = 1000000000000000;
    long check17 = 10000000000000000;

    if (cc >= check13 && cc < check17)
    {
        if (cc >= check13 && cc < check14)
        {
            if (cc / check13 == 4)
            {
                if (checksum(cc, 13))
                {
                    return "VISA\n";
                }
                else
                {
                    return "INVALID\n";
                }
            }
            else
            {
                return "INVALID\n";
            }
        }
        else if (cc >= check15 && cc < check16)
        {
            if (cc / check14 == 34 || cc / check14 == 37)
            {
                if (checksum(cc, 15))
                {
                    return "AMEX\n";
                }
                else
                {
                    return "INVALID\n";
                }
            }
            else 
            {
                return "INVALID\n";
            }
        }
        else if (cc >= check16 && cc < check17)
        {
            if (cc / check16 == 4)
            {
                if (checksum(cc, 16))
                {
                    return "VISA\n";
                }
                else
                {
                    return "INVALID\n";
                }
            }
            else if (cc / check15 >= 51 && cc / check15 <= 55)
            {
                if (checksum(cc, 16))
                {
                    return "MASTERCARD\n";
                }
                else
                {
                    return "INVALID\n";
                }
            }
            else
            {
                return "INVALID\n";
            }
        }
        else 
        {
            return "INVALID\n";
        }
    }

    else 
    {
        return "INVALID\n";
        
    }
}

bool checksum (long cc, int check)
{
    int sum;
    int multSum;
    int digit;
    int checkSum;

    for (int i = 1; i <= check; i++)
    {
        digit = cc % 10;
        if (i % 2 == 0)
        {
            if (digit > 4)
            {
                multSum += 1 + ((digit * 2) % 10);
            }
            else
            {
                multSum += digit * 2;
            }
        }
        else
        {
            sum += digit;
        }
        cc = (cc - digit) / 10;
    }
    
    checkSum = sum + multSum;
    
    if (checkSum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
