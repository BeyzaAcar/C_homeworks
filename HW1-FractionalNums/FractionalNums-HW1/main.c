#include <stdio.h>
#include "utils.h"


int main()
{
    int x, y, z, f_I, n, nth_divisible, password;
    char identity_number[111], id_login[111];
    float cash_amount;
	printf("Enter the first integer: ");
	scanf("%d", &x);
	printf("Enter the second integer: ");
	scanf("%d", &y);
	printf("Enter the divisor: ");
	scanf("%d", &z);
	f_I = find_divisible(x, y, z);
	if(f_I == -1)
        printf("There is not any integer between %d and %d can be divided by %d\n", x, y, z);
    else
    {
        printf("The first integer between %d and %d divided by %d is %d\n", x, y, z, f_I);
        printf("Enter the number how many next: ");
		scanf("%d", &n);
		nth_divisible = find_nth_divisible(n, f_I, z);
		if(nth_divisible>y)
    	{
    	    printf("No possible to find %d. divisible between %d and %d divided by %d", n, x, y, z);
    	    return -999;
   		}
   		else
        	printf("The %d. integer between %d and %d divided by %d is %d\n", n+1, x, y, z, nth_divisible);
   	}

    printf("Enter your identity number: ");
    scanf("%s", identity_number);
    printf("Enter your password: ");
    scanf("%d", &password);
    if(validate_identity_number(identity_number) && (password/1000) && !(password/10000))
    {
        printf("Your ID and password have been accepted\n");
        create_customer(identity_number, password);
        printf("Enter your ID: ");
        scanf("%s", id_login);
        printf("Enter your password: ");
        scanf("%d", &password);
        if(check_login(id_login, password))
        {
            printf("Login succesful\n");
			printf("Enter your withdraw amount: ");
        	scanf("%f", &cash_amount);
        	printf("Withdrawable amount is: %d\n", withdrawable_amount(cash_amount));
        }
        else
        {
        	printf("Invalid identity number or password");
        }
    }
    else
    {
        printf("Invalid identity number or password\n");
        return 0;
    }
    return(0);
}
