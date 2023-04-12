#include<stdio.h>
#include<stdlib.h>
#include"util.h"

int main()
{
    int seqlen, xs, i, a, h[10]; 
    for(i=0;i<10;i++) h[i] = 0;
    int *looplen = &a;
    int *loop = (int*)malloc(sizeof(int)*seqlen); /*loop dizisi aciyorum heap memory'de*/
    loop[0] = -2; /*bunu yapma sebebim diziyi bir kere printlemek istemem, diziyi printledikten sonra 0.elemani degistirerek tekrar printlememesini sagliyorum*/
    printf("Please enter the sequance length..:");
    scanf("%d", &seqlen);
    *looplen = seqlen/2; /*seqlen boyutunda bir dizide maksimum dizi boyutunun yarısında loop bulunabilecegi icin loop'u eleman sayisinin yarisindan baslatiyorum*/
    printf("Please enter the first element..:");
    scanf("%d", &xs); /*olusturacagimiz dizi icin ilk elemanimizi yani seed aliyorum*/
    check_loop_iterative(generate_sequence, xs, seqlen, loop, looplen);
    if((*looplen) <= 1) printf("No loop found\n"); /*looplen 1 e ulastiysa ve hala loop bulunamadiysa, minimum loop 2 oldugundan loop'un bulunamadigini bastiriyorum*/
    else 
    {
        printf("Loop : ");
        for(i=0;i<(*looplen);i++) printf("%d ", loop[i]);
    }
    hist_of_firstdigits(generate_sequence, xs, seqlen, h, 1);
    printf("\nHistogram of the array : ");
    for(i=0;i<9;i++) printf("%d ", h[i]);
    printf("\n");
    free(loop);
    return 0;
}
