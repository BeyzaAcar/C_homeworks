#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*butun fonksiyonları tanimliyorum*/
int dice ();
int startGame ();
void printMap (char dizi[15][30], int);
int oyun_akisi(int);

/*RENKLERI RAHAT KULLANILMASI ICIN FONKSIYON YAPTIM*/

void yellow() { printf("\033[0;33m"); }
void red() { printf("\033[1;31m"); }
void blue() { printf("\033[0;34m"); }
void green() { printf("\033[0;32m"); }
void reset() { printf("\033[0m"); }

int dice ()
{
    srand(time(NULL));
    int rastgele;
    rastgele = rand()%6+1;
    return rastgele;
}

int startGame ()
{
    int rastgele1, rastgele2; 
    do
    {
        printf("\nPLAYER 1... PRESS ENTER TO ROLL THE DICE:\n");
        getchar();
        rastgele1 = dice();
        printf("\nDICE : %d\n", rastgele1);
        printf("\nPLAYER 2... PRESS ENTER TO ROLL THE DICE:\n");
        getchar();
        rastgele2 = dice();
        printf("\nDICE : %d\n", rastgele2);
        if(rastgele1 == rastgele2) printf("\nplease try again\n");
    } while(rastgele1 == rastgele2);
    if(rastgele1>rastgele2) return 1;
    else return 2;
}


/*
MAP ORNEK CIZIM
..............................
:              X             : 
: .......................... :
: :      X           X     : : 
: : ...................... : : 
: : :                    :X: :  
: : :                    : : : 
: : :                    : :X: 
: : :                    : : : 
: : :                    : : : 
: : ......................X: : 
: :      X           X     : : 
: .......................... :
:              X             : 
..............................

*/



int oyun_akisi(int start)
{
    char dizi[15][30];
    int i, j, dice1, dice2, hareket_yonu_1=1, hareket_yonu_2=1, kazanan1=0, kazanan2=0, tek_sefer = 0; /*
    hareket_yonu 1 ise saga,
    hareket_yonu 2 ise asagi,
    hareket_yonu 3 ise sola,
    hareket_yonu 4 ise yukari hereket ediyor anlamina geliyor.
    */
   /*kazanan1 ve kazanan2 birer flag, hangi oyuncu bitirdiyse onun flagi bir oluyor, 
   eger aynı anda bitirdilerse start degiskenine bakilarak kazanan belirleniyor*/
    int yer_1_i = 1, yer_1_j = 1; /*baslangictaki yerlerini belirtiyorum*/
    int yer_2_i = 3, yer_2_j = 3; /*birinci ve ikinci oyuncunun i ve j olarak yerlerini ifade ediyor*/
    do
    {
        
        for(i=0;i<15;i++)
        {
            for(j=0;j<30;j++)
            {
                if(i==0 || i ==14 ) dizi[i][j] = '.';
                else if(i==1 || i==28)
                {
                    if(j==0 || j==29) dizi[i][j] = ':';
                    else dizi[i][j] = ' ';
                } 
                else if(i==1 || i==13)
                {
                    if(j==0 || j==29) dizi[i][j] = ':';
                    else dizi[i][j] = ' ';
                }
                else if(i==2 || i== 12)
                {
                    if(j==0 || j== 29) dizi[i][j] = ':';
                    else if(j==1 || j==28) dizi[i][j] = ' ';
                    else dizi[i][j] = '.';
                } 
                else if(i==3 || i == 11)
                {
                    if(j==0 || j==2 || j==29 || j==27) dizi[i][j] = ':';
                    else dizi[i][j] = ' ';
                }
                else if(i==4 || i==10)
                {
                    if(j==0 || j==2 || j==29 || j==27) dizi[i][j] = ':';
                    else if(j==1 || j==3 || j==28 || j==26) dizi[i][j] = ' ';
                    else dizi[i][j] = '.';
                }
                else
                {
                    if(j==0 || j==2 || j==4 || j==29 || j==27 || j==25) dizi[i][j] = ':';
                    else dizi[i][j] = ' ';
                }
            }
        }
        /* tek tek 'X' leri ve '_' yerlestiriyorum */
        dizi[1][14] = 'X';
        dizi[7][28] = 'X';
        dizi[13][14] = 'X';
        dizi[3][10] = 'X';
        dizi[3][18] = 'X';
        dizi[5][26] = 'X';
        dizi[10][26] = 'X';
        dizi[11][10] = 'X';
        dizi[11][18] = 'X';
        dizi[2][1] = '_';
        dizi[4][3] = '_';
        if(tek_sefer == 0)
        {
            printMap(dizi, 0);
            tek_sefer++;
            dizi[1][1] = ' ';
            dizi[3][3] = ' ';
        }
        if(start == 1)
        {
            yellow();
            printf("\nPLAYER 1, ROLL THE DICE..: \n");
            getchar();
            dice1 = dice();
            printf("\nDICE : %d\n", dice1);
            blue();
            printf("\nPLAYER 2, ROLL THE DICE..: \n");
            getchar();
            dice2 = dice();
            printf("\nDICE : %d\n", dice2);
            reset();
        }
        else
        {
            blue();
            printf("\nPLAYER 2, ROLL THE DICE..: \n");
            getchar();
            dice2 = dice();
            printf("\nDICE : %d\n", dice2);
            yellow();
            printf("\nPLAYER 1, ROLL THE DICE..: \n");
            getchar();
            dice1 = dice();
            printf("\nDICE : %d\n", dice1);
            reset();
        }

        /*BIRINCI OYUNCU*/
        if(hareket_yonu_1 == 1) /*SAG*/
        {
            if(yer_1_j+dice1>28) 
            {
                yer_1_i = yer_1_i+((yer_1_j+dice1)-28);
                yer_1_j = 28;
                hareket_yonu_1++; /*hareket yonu degisti*/
            }
            else if(dizi[1][yer_1_j+dice1] == 'X') 
            {
                yer_1_j = yer_1_j+dice1-2;
                printf("\nPenalty for player 1 :(\n");
            }
            else yer_1_j += dice1;
        }
        else if(hareket_yonu_1 == 2) /*ASAGİ*/
        {
            if(yer_1_i+dice1>13)
            {
                yer_1_j = yer_1_j-((yer_1_i+dice1)-13);
                yer_1_i = 13;
                hareket_yonu_1++;
            }
            else if(dizi[yer_1_i+dice1][28] == 'X') 
            {
                yer_1_i = yer_1_i + dice1 - 2;
                printf("\nPenalty for player 1 :(\n");
            }
            else yer_1_i += dice1;
        }
        else if(hareket_yonu_1 == 3) /*SOL*/
        {
            if(yer_1_j-dice1<1)
            {
                yer_1_i = yer_1_i - dice1 + (yer_1_j-1);
                yer_1_j = 1;
                hareket_yonu_1++;
            }
            else if(dizi[13][yer_1_j-dice1] == 'X') 
            {
                yer_1_j = yer_1_j - dice1 + 2;
                printf("\nPenalty for player 1 :(\n");
            }
            else yer_1_j -=dice1;
        }
        else /*YUKARI*/
        {
            if(yer_1_i-dice1<3)
            {
                yer_1_i = 2;
                kazanan1 = 1;
            }
            else yer_1_i -= dice1;
        }

        //  IKINCI OYUNCU
        if(hareket_yonu_2 == 1) /*SAG*/
        {
            if(yer_2_j+dice2>26) 
            {
                yer_2_i = yer_2_i+((yer_2_j+dice2)-26);
                yer_2_j = 26;
                hareket_yonu_2++; /*hareket yonu degisti*/
            }
            else if(dizi[3][yer_2_j+dice2] == 'X') 
            {
                yer_2_j = yer_2_j + dice2 - 2;
                printf("\nPenalty for player 2 :(\n");
            }
            else yer_2_j += dice2;
        }
        else if(hareket_yonu_2 == 2) /*ASAGİ*/
        {
            if(yer_2_i+dice2>11)
            {
                yer_2_j = yer_2_j-((yer_2_i+dice2)-11);
                yer_2_i = 11;
                hareket_yonu_2++;
            }
            else if(dizi[yer_2_i+dice2][26] == 'X') 
            {
                yer_2_i = yer_2_i + dice2 - 2;
                printf("\nPenalty for player 2 :(\n");
            }
            else yer_2_i += dice2;
        }
        else if(hareket_yonu_2 == 3) /*SOL*/
        {
            if(yer_2_j-dice2<3)
            {
                yer_2_i = yer_2_i - (dice2 - (yer_2_j-3));
                yer_2_j = 3;
                hareket_yonu_2++;
            }
            else if(dizi[11][yer_2_j-dice2] == 'X') 
            {
                yer_2_j = yer_2_j-dice2+2;
                printf("\nPenalty for player 2 :(\n");
            }
            else yer_2_j -=dice2;
        }
        else /*YUKARI*/
        {
            if(yer_2_i-dice2<5)
            {
                yer_2_i = 4;
                kazanan2 = 1;
            }
            else yer_2_i -= dice2;
        }
        dizi[yer_1_i][yer_1_j] = '1';
        dizi[yer_2_i][yer_2_j] = '2';
        printMap(dizi, 1);
    } while(kazanan1 != 1 && kazanan2 != 1);
    if(kazanan1 == 1 && kazanan2 == 1)
    {
        if(start == 1) printf("\nBIRINCI OYUNCU KAZANDI !!!\n");
        else printf("\nIKINCI OYUNCU KAZANDI !!!\n");
    }
    else if(kazanan1 == 1) printf("\nBIRINCI OYUNCU KAZANDI !!!\n");
    else printf("\nIKINCI OYUNCU KAZANDI !!!\n");

}

void printMap (char dizi[15][30], int ilk) /*eger ilk degiskeni 0 sa baslangic mapi cizilecek yoksa normal oyuna baslanacak*/ 
{
    int i, j;
    if(ilk == 0)
    {
        dizi[1][1] = '1';
        dizi[3][3] = '2';
    }
    for(i=0;i<15;i++)  /*DIZIYI PRINTLEME KISMI*/
    {
        for(j=0;j<30;j++)
        {
            if(dizi[i][j] == 'X')
            {
                red();
                printf("%c", dizi[i][j]);
                reset();
            }
            else if(dizi[i][j] == '_')
            {
                green();
                printf("%c", dizi[i][j]);
                reset();
            }
            else if(dizi[i][j] == '1') 
            {
                yellow();
                printf("%c", dizi[i][j]);
                reset();
            }
            else if( dizi[i][j] == '2')
            {
                blue();
                printf("%c",  dizi[i][j]);
                reset();
            }
            else printf("%c", dizi[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

int main()
{
    printf("Before the game begins, two players will roll the dice"
    "and it will be decided who starts first.");
    int start = startGame();
    oyun_akisi(start);
    return 0;
}
