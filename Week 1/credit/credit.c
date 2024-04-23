#include <cs50.h>
#include <stdio.h>

int check_sum(long long n);

int main(void)
{
    // Wait for input
    long long card_num = get_long("Digite o número do cartão: ");

    //Check if the is valid(with Luhn's Algorithm)
    int flag_sum = check_sum(card_num);



    //If is a Invalid (sum module ten != 0) then return INVALID msg
    if (flag_sum == 1)
    {
        printf("INVALID\n");
    }
    else
    {
        //Check the initial values are compatible by VISA or Mastercard or AMEX cards

        long long tentotwelve = 1000000000000;
        long long tentothirteen = 10000000000000;
        long long tentofourteen = 100000000000000;
        long long tentofifteen = 1000000000000000;
        if(card_num / tentofifteen == 4 || card_num / tentotwelve == 4)
        {
            printf("VISA\n");
        }
        else if(card_num/tentofourteen <=55 && card_num/tentofourteen > 50)
        {
            printf("MASTERCARD\n");
        }
        else if(card_num/tentothirteen == 34 || card_num/tentothirteen == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

int check_sum(long long n)
{
    //This functions receive a credit card and verify if is a validy card number(with Luhn's algorithm)
    int sum = 0;
    while (n > 0)
    {
        //In each loop, the last 2 digits are taken, the second is multiplied and
        // added to the sum variable
        int last_digit = n % 10;
        n /= 10;
        int sec_lastdigit = n % 10;
        int dup_sec_lastdigit = sec_lastdigit *2;
        if (dup_sec_lastdigit > 9)
        {
            int firstintnum = dup_sec_lastdigit%10;
            dup_sec_lastdigit /= 10;
            sum += dup_sec_lastdigit + firstintnum + last_digit;
        }
        else
        {
            sum += (sec_lastdigit*2 + last_digit);
        }
        n /= 10;
    }
    //if the sum modulus is equal to 0, it returns 0 (it's valid card)
    if (sum % 10 == 0)
    {
        return 0;
    }
    else{
        return 1;
    }
}