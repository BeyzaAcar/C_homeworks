#include <stdio.h>
#include "util.h"


/* Example decision tree - see the HW2 description */
int dt0(int t, double p, double h, char s, int w) {
    int r = 0;
    if (t>35 && w!=3) r = 1;
    else if (t<=35 && s==0) r = 1;
    return r;
}

char dt1a(double pl, double pw, double sl, double sw)
{
    if(pl<2.45)
    {
        return 'o';
    }
    else
    {
        if(!(pw<1.75))/*bunu daha duzenli gorunuyor diye yaptim. return u ilk yapinca daha duzgun duruyordu. Else if yerini degistirmis oldum bunu yaparak*/ /*buyuk esit de yapabilirdim*/
        {
            return 'g';
        }
        else
        {
            if(!(pl<4.95))
            {
                return 'g';
            }
            else
            {
                if(pw<1.65)
                    return 's';
                else return 'g';
            }
        }
    }
}
char dt1b(double pl, double pw, double sl, double sw)
{
    if(pl<2.55)
    {
        return 'o';
    }
    else
    {
        if(!(pw<1.69))
        {
            return 'g';
        }
        else
        {
            if(pl<4.85) return 's';
            else return 'g';
        }
    }
}
double dt2a(double x1, double x2, double x3, int x4, int x5)
{
    if(x1<31.5)
    {
        if(x2>-2.5)
        {
            return 5.0;
        }
        else
        {
            if(x1>=x2-0.1 || x1<=x2+0.1) return 2.1;
            else return -1.1;
        }
    }
    else
    {
        if(x3>=-1 && x3<=2)
        {
            return 1.4;
        }
        else
        {
            if(x4 && x5)
            {
                return -2.23;
            }
            else
            {
                return 11.0;
            }
        }
    }
}

double dt2b(double x1, double x2, double x3, int x4, int x5)
{
    if(x1<22 && x1>12)
    {
        if(x3>(double)5/3)
        {
            return -2.0;
        }
        else
        {
            if(x3>=x1-0.1 && x3<=x1+0.1)
            {
                return 1.01;
            }
            else
            {
                return -8;
            }
        }
    }
    else
    {
        if(x4 && x5)
        {
            return -1;
        }
        else
        {
            if(x2>=-1 && x2<=2)
            {
                return (double)-1/7;
            }
            else
            {
                return 0.471405; /*hesap makinesiyle degeri hesaplayip
                6 basamak olacak sekilde yuvarladim*/
            }
        }
    }
}

int GTU(double uyku, char y_n, double ders, int stres, int tatil)
{
    if(uyku>5)
    {
        return 0;
    }
    else
    {
        if(y_n=='y')
        {
            return 0;
        }
        else
        {
            if(ders<24)
            {
                return 0;
            }
            else
            {
                if(stres!=5)
                {
                    return 0;
                }
                else
                {
                    if(tatil!=1)
                    {
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                }
            }
        }
    }
}
/*
1 = zeytinyagli sarma
2 = hamsi tava
3 = tavuık durum
4 = körili tavuklu mantarli sote
5 = etli sebzeli guvec
6 = et doner
7 = biftek
8 = tavuklu mantarli sote
*/

int yemek(int et, char et_tipi, int sebze, char ev_fast, char baharat)
{
    if(et==0)
    {
        return 1;
    }
    else
    {
        if(et_tipi == 'b')
        {
            return 2;
        }
        else if(et_tipi == 't')
        {
            if(ev_fast == 'f')
            {
                return 3;
            }
            else
            {
                if(baharat == 'y')
                {
                    return 4;
                }
                else
                {
                    return 8;
                }
            }
        }
        else
        {
            if(sebze>3)
            {
                return 5;
            }
            else if(ev_fast == 'f')
            {
                return 6;
            }
            else
            {
                return 7;
            }
        }
    }
}

/* Provide your implementations for all the requested functions here */

