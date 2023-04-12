#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) 
{
    printf("%d//%d", numerator, denominator);
}
void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) 
{
	*n3 = n1*d2 + n2*d1;
	*d3 = d1*d2;
	fraction_simplify(n3, d3);
}

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) 
{	
	*n3=n1*d2-n2*d1;
	*d3=d1*d2;
	fraction_simplify(n3, d3);
} 

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) 
{
	*n3=n1*n2;
	*d3=d1*d2;
   	fraction_simplify(n3, d3);
}

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3)
{
	*n3=n1*d2;
	*d3=n2*d1;
   	fraction_simplify(n3, d3);
}

void fraction_simplify(int * n, int * d) 
{
	int tut = 2;
    int GCD = 1;
    int temp_nom = *n;
    if(*n < 0) /*eger sayi negatif olursa while a girmiyordu bu yuzden gecici iki degisken actim ve pay veya payda negatifse bu gecici sayilari bunların pozitiflerine eşitledim boylelikle GCD yi bulabilecegim */
    {
    	temp_nom = (*n)*(-1);
    }
    
    while(tut<=temp_nom) /*temp_nom ya da temp_denom olmasinin bir onemi olmadigi icin ikisinden birini kullandim*/
    {
        if(*d%tut==0 && *n%tut==0)
        {
            GCD =  tut;
        }
        tut++;
    }
    *n = *n / GCD;
    *d = *d / GCD;
    if(*n < 0 && *d < 0) /*burasi, kesirin payi ve paydasi negatifse -5/-6 değil de 5/6 seklinde gostermesi icin */ 
    {
    	*n = (*n) * (-1);
    	*d = (*d) * (-1);
    }
    else if(*d < 0) /* burayi eger payda negatif ve pay pozitifse 5/-6 diye degil de -5/6 diye gostersin diye yaptim*/
    {
    	*n = (*n) * (-1);
    	*d = (*d) * (-1);
    }
}
