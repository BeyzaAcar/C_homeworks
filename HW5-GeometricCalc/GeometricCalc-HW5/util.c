#include<stdio.h>
#include<stdlib.h>
#include"util.h"

void generate_sequence (int xs, int currentlen, int seqlen, int *seq) /*istenilen sekilde dizi olusturuyor
																	sayi cift ise ikiye boluyor degilse 3 katina bir ekleyerek fonksiyona tekrar gonderiyor*/
{
    if(currentlen != 0) /*currentlen, seqlen(dizi boyutu)'den baslayip azalarak gidiyor, bu yuzden 0 a ulastiginda durmasini sagliyorum*/
    {
    	seq[seqlen-currentlen] = xs;
        if(xs%2 == 0) generate_sequence(xs/2, currentlen-1, seqlen, seq);
        else generate_sequence(3*xs+1, currentlen-1, seqlen, seq);
    }
}

int has_loop(int *arr, int n, int looplen, int *ls, int *le) /*loop kontrolu yapiyor ve varsa 1, yoksa 2 donduruyor*/
{
    printf("Checking if there is a loop of length %d\n", looplen);
    int i, k = 0;
    for(i=0;i<n-looplen;i++) /*dongu, n-looplen kadar donuyor cunku daha fazla donerse dizinin var olmayan ileriki elemanlarina ulasmaya calisip hata verir*/
    {
        if(arr[i+looplen] == arr[i]) 
        	while(i+looplen+k<n && arr[i+k] == arr[i+looplen+k]) k++; /*bir esitlik buldugu an while dongusune girip bastaki i degerini kaybetmeden kontrol etmeye devam ediyor, eger loopl bulamazsa bastaki i degerini kaybetmedigimiz icin bastaki i ye geri donup tekrar deniyor*/
        if(k>=looplen)
        {
            *ls = i;
            *le = i+looplen-1;
            return 1;
        }
    }
    return 0;
}

void check_loop_iterative(void (*generate)(int, int, int, int *), int xs, int seqlen, int *loop, int *looplen) /*has loop fonksiyonu aracaligiyla loop kontrolu yapiyor ve loop un ilk ve son elemanlarini maine gonderebilmek adina adreslerini aldigimiz integerlara yerlestiriyor*/
{
    int ls, le, i, *seq;
    seq = (int*)malloc(sizeof(int)*seqlen);
    (*generate)(xs, seqlen, seqlen, seq);
    if(loop[0] == -2) /*buraya bir kere girsin diye yaptim*/
    {
        for(i=0;i<seqlen;i++) printf("%d ", seq[i]);
        printf("\n\n");
        loop[0] = -1;
    }
    if(has_loop(seq, seqlen, (*looplen), &ls, &le))
    {
        for(i=0;i<(*looplen);i++) loop[i] = seq[(ls)+i];
        printf("\nLoop detected with a length of %d\n", *looplen);
        printf("\nThe indexes of the loop's first occurance: %d (first digit), %d (last digit)\n\n", ls, le);
        free(seq);
    }
    else
    {
        free(seq);
        (*looplen) = (*looplen)-1;
        if((*looplen) > 1) check_loop_iterative(generate_sequence, xs, seqlen, loop, looplen);
    }
}

int ilk_basamak(int sayi)/*ilk basamagi donduruyor. Orn cikti : code : printf("ilk_basamak(4562)")  output = 4*/
{
    int pow = 1;
    while(sayi/pow != 0) pow = pow*10;
    return sayi/(pow/10);
}

void hist_of_firstdigits(void (*generate)(int, int, int, int *), int xs, int seqlen, int *h, int digit) /*seedini kullanicidan aldigimiz ve bu seed ile olusturdugumuz dizinin ilk basamaklarina gore dagilimini h dizisine atiyor*/
{
    int *seq, i;
    seq = (int*)malloc(sizeof(int)*seqlen);
    (*generate)(xs, seqlen, seqlen, seq);
    if(seqlen>=digit)
    {
        h[ilk_basamak(seq[digit-1])-1]++;
        free(seq);
        hist_of_firstdigits(generate_sequence, xs, seqlen, h, digit+1);
    }
}
