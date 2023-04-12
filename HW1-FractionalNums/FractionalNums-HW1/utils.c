#include <stdio.h>
#include "utils.h"

int find_divisible(int x, int y, int z)
{
    while(x<=y)
    {
        if(!(x%z))
            return x;
        x++;
    }
    return -1;
}

int find_nth_divisible(int n, int f_I, int z)
{
    return (f_I+z*n);
}

//PART 2
int validate_identity_number(char identity_number [])
{
    char *str = identity_number; /* ismi kolaylik saglasin diye yaptim tamamen*/
    int i = 0, kontrol_1 = 0, kontrol_2 = 0, toplam = 0;/*"kontrol_1" hepsinin sayi olup olmadigini kontrol eden "kontrol_1" degiskeni eger 11'e esitse hepsi sayidir demektir. kontrol_2
     degiskenini dorduncu kontrolu saglamak icin yaziyorum: 1 3 5 7 ve 9.hanelerdeki sayilarin toplaminin 7 katindan 2 4 6 8. hanelerdeki sayilarin
     toplamini cikarip 10 ile modunu alip 10. hanedeki sayiyla karsilastiracagim. "toplam" degiskenini 5.kontrol icin yazdim, ilk 10 basamaklari toplayip 10 ile modunu
     alacagim ve 11. haneye esit mi diye bakacagim */
    while(str[i])
    {
        if(str[i]>= '0' && str[i] <= '9')
            kontrol_1++;
        toplam = toplam + (str[i]-'0'); /* '0' cikarma sebebim karakter olan sayiyi integar a cevirebilmek*/
        i++;
    }
    kontrol_2 = ((((str[0] + str[2] + str[4] + str[6] + str[8])-'0'*5)*7)- ((str[1] + str[3] + str[5] + str[7])-'0'*4))%10;
    if(i==11 && str[0] && kontrol_1 == 11 && kontrol_2 == str[9]-'0' && (toplam-(str[10]-'0'))%10 == str[10]-'0')
    {
        return 1;
    }
    else
        return 0;
}

int create_customer(char identity_number [], int password)
{
    int i = 0, basamak = 1000;
    char password_str[5];
    if(password/1000 && !(password/10000))
    {
        FILE *fileptr = fopen("customeraccount.txt", "w"); /*dosyayi yazma modu ile acip icine yaziyorum*/
        fprintf(fileptr,"%s,%d", identity_number, password);
        fclose(fileptr);
        return 1;
    }
    else
        return 0;
}

//PART 3
int check_login(char identity_number [], int password)
{
 	/*bu bolumde dosyaya yazdigimda otomatik char a donustugunden okurken int diye okutamadim cunku butun bir char dizisinde 11. basamakta durmasi gerekiyor kalan charlari int olarak okumasi gerekiyor, ben bunun yerini passwordu de char dizisine donusturdum butun icerigi ( id ve password ) genel_control dizisine attim, onunla kontrolu sagladim*/
    int i = 0, basamak = 1000; /*basamagin amaci sayinin basamaklarini tek tek elde edebilip char a cevirebilmek*/
    char genel_kontrol[20], identity_control[20];
    while(i<11)
    {
        genel_kontrol[i] = identity_number[i];
        i++;
    }
    genel_kontrol[11] = ',';
    i = 12;
    while(i<16)
    {
        genel_kontrol[i] = ((password/basamak)%10) + '0';
        i++;
        basamak = basamak / 10;
    }
    FILE *fileptr = fopen("customeraccount.txt", "r");
    fscanf(fileptr, "%s", identity_control); /*butun datayi (id ve password) bu diziye attim */
    i = 0;
    while(identity_control[i])
    {
        if(genel_kontrol[i] != identity_control[i])
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int withdrawable_amount(float cash_amount)
{
	cash_amount = cash_amount - ((int)cash_amount%10);
    return (int)cash_amount;
}
