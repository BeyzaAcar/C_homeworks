#include <stdio.h>
#include <stdlib.h>
#include "util.h"


int main()
{

    /* Ask for the problem selection (1,2,3) .....  */
    double sl, sw, pl, pw, x1, x2, x3, uyku, ders;
    int dt, x4, x5, stres, tatil, resss_1, resss_2, et, sebze, kontrol; /*(dt=decision tree)*/
    char res_1, res_2, y_n, ev_fast, baharat, et_tipi; /*results for the first decision tree*/
    float ress_1, ress_2; /* results for the second decision tree*/
    while(1)
    {
        printf("Please select the decision tree (1, 2 or 3):  ");
        scanf("%d", &dt);
        if(!(dt==1 || dt==2 ||dt==3)) printf("Please try again, you should enter 1 for the first decision tree, 2 for the second decision tree or 3 for the third one\n");
        else break;
    }
    if(dt==1)
    {
        printf("Please enter pl, pw, sl ,sw sequentially :  ");
        scanf("%lf %lf %lf %lf", &pl, &pw, &sl, &sw);
		res_1=dt1a(pl, pw, sl, sw);
		res_2=dt1b(pl, pw, sl, sw);
        if(res_1 == res_2)
        {
            if(res_1=='o') printf("Setosa");
            else if(res_1=='g') printf("Virginica");
            else printf("Versicolor");
        }
        else
        {
            printf("Results are different. Results :");
            if(res_1=='o') printf("Setosa and ");
            else if(res_1=='g') printf("Virginica and ");
            else printf("Versicolor and ");
            if(res_2=='o') printf("Setosa ");
            else if(res_2=='g') printf("Virginica ");
            else printf("Versicolor ");
            printf("\n");
        }
    }
    else if(dt==2)
    {
        printf("Please enter x1, x2, x3 sequentially..:");
        scanf("%lf %lf %lf", &x1, &x2, &x3);
        printf("Please enter x4 and x5");
        scanf("%d %d", &x4, &x5);
        while(1)
        {
            if(!((x4==1 || x4==0) && (x5==1 || x5==0)))
            {
                printf("Please enter a suitable number for x4 and x5(1 or 0)\n"); /*x4 veya x5 0 ya da 1'e esit degilse*/
                scanf("%d %d", &x4, &x5);
            }
            else break;
        }
        ress_1=dt2a(x1 ,x2, x3, x4, x5);
        ress_2=dt2b(x1 ,x2, x3, x4, x5);
        if(ress_1-ress_2<CLOSE_ENOUGH && ress_1-ress_2>(CLOSE_ENOUGH*(-1)))
        /*farklarinin mutlak degeri close_enough degerinden kucukse*/
            printf("Results are pretty close, avarage of results is : %f\n", (ress_1+ress_2)/2); /*ortalama yazdiriyorum*/
        else
            printf("Results are not close. First result is: %lf and the second result is: %lf\n", ress_1, ress_2);
    }
    else
    {
        printf("GTU'DE HAYATTA KALABILIR MISIN TESTINE HOSGELDINIZ! LUTFEN ASAGİDAKİ SORULARI CEVAPLAYİNİZ\n");
        printf("Gunluk kac saat uyursunuz: ");
        scanf("%lf", &uyku);
        printf("Sosyal etkinlikleri onemser misin..: (y for yes and n for no)");
        getchar(); /* nedense enter i aliyordu bu yuzden ekledim butun getcharlari*/
        scanf("%c", &y_n);
        printf("Final haftasinda gunde maksimum kac saat calisabilirsin..: ");
        scanf("%lf", &ders);
        printf("Stresle 5 uzerinden kac basa cikabilirsiniz..: ");
        scanf("%d", &stres);
        printf("Tatil yapmak senin icin ne derece onemli(1-5)..: ");
        scanf("%d", &tatil);

        if(GTU(uyku, y_n, ders, stres, tatil))
        {
            printf("Tebrikler, GTU'de hayatta kalabilirsiniz!!!!\n");
        }
        else
        {
            printf("Maalesef... GTU'de hayatta kalamadiniz...\n");
        }
        printf("En Sevdiginiz Yemeklerden Birini Tahmin Ediyoruz testine hosgeldiniz!!!\n");
        printf("Lutfen et seviyorsaniz 1 sevmiyorsanız 0 giriniz..:");
        scanf("%d", &et);
        getchar();
        printf("Eger et seviyorsaniz hangi cesidini daha cok sevdiginizi giriniz (b=balik, t=tavuk, k=kirmizi et)..:");
        scanf("%c", &et_tipi);
        printf("Sebzeyi ne derece sevdiginizi giriniz..: (1-5)  ");
        scanf("%d", &sebze);
        getchar();
        printf("Daha cok ev yemegi mi fast food mu tercih edersin(e=ev yemegi, f=fast food)");
        scanf("%c", &ev_fast);
        getchar();
        printf("baharat sevip sevmediginizi giriniz..:(y/n)");
        scanf("%c", &baharat);
        kontrol = yemek(et, et_tipi, sebze, ev_fast, baharat);
        if(kontrol == 1)
        {
            printf("siz zeytinyagli sarma seviyorsunuz");
        }
        else if(kontrol == 2)
        {
            printf("siz hamsi tava seviyorsunuz\n");
        }
        else if(kontrol == 3)
        {
            printf("siz tavuık durum seviyorsunuz\n");
        }
        else if(kontrol == 4)
        {
            printf("siz körili tavuklu mantarli sote seviyorsunuz\n");
        }
        else if(kontrol == 5)
        {
            printf("siz etli sebzeli guvec seviyorsunuz\n");
        }
        else if(kontrol == 6)
        {
            printf("siz et doner seviyorsunuz\n");
        }
        else if(kontrol == 7)
        {
            printf("siz biftek seviyorsunuz\n");
        }
        else if(kontrol == 8)
        {
            printf("siz  tavuklu mantarli sote seviyorsunuz\n");
        }
    }


    /* Get the input from the user for the first problem, i.e., to test dt1a and dt1b */
    /* Compare performances and print results */

    /* Get the input from the user for the second problem, i.e., to test dt2a and dt2b */
    /* Compare performances and print results */

    /* Get the input from the user for the third problem, i.e., to test dt3a and dt3b */
    /* Compare performances and print results */

    return 0;
}

