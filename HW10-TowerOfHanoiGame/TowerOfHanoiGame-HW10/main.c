#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define STACK_BLOCK_SIZE 10
typedef struct 
{
    int *array;
    int currentsize;
    int maxsize;
} stack;

stack *init_return() /* initializes an empty stack */
{
    stack *towers = (stack *) malloc(sizeof(stack)*3); /*3 farkli alan icin birer stack aciyorum*/
    return towers;
}

int init(stack *s) /*returns one if initialization is succesfull*/
{
    if(s != NULL) return 1;
    else return 0;
}

void push(stack *s, int d)
{
    if(s->currentsize != s->maxsize)
    {
        s->array[(s->currentsize)] = d;
        s->currentsize++;
    }
}

int pop(stack *s)
{
    s->currentsize--;
    return s->array[s->currentsize+1];
}

void game(int disk_number, stack *towers)
{
    int i, j, k, flag = 0; /*i j, k ic ice forlar icin*/
    int son_duzenlenen=-1, max = -1, sinir = 20000, max_index = 0, siradaki;
    for(j=0;j<pow(2, disk_number)-1;j++) /*2 uzeri disk sayisinin bir eksigi toplam yapilmasi gereken hamleyi veriyor bu for dongusu hamle sayisi icin orn disk sayisi 5 ise toplam hamle sayisi 2^5-1 = 31*/
    {
        max_index = 0;
        sinir = 20000; /*rastgele buyuk bir sayi verdim*/
        for(k=0;k<3;k++)
        {
            max = 0; /*max degiskeni yukaridan uc stack e baktigimizda gordugumuz stackler arasindaki en buyugunu ifade ediyor orn: stack 1 : 0321*/
            for(i=0;i<3;i++) /*max index = ustteki bloklardaan yuksek olanin hangisinde oldugunu soyluyor*/
            {
                if(max<towers[i].array[(towers[i].currentsize)-1] && towers[i].array[(towers[i].currentsize)-1]<sinir) 
                {
                    max = towers[i].array[(towers[i].currentsize)-1];
                    max_index = i;
                }
            }
            sinir = max;
            if(son_duzenlenen != max) /*son degistirilen diske bir sonraki hamlede dokunmasina izin vermiyorum*/
            {
                if(disk_number%2 == 0) /*eger disk sayisinin tek ciftligini kontrol etmezsem %50 ihtimalle 3. degil 2.stackte topluyor dolayisiyla move sayisi 2 katina cikiyor*/
                {					   /*ama disk sayisini kontrol ettigimde minimum hareketle diskleri 3.stackte toplamis oluyorum*/
                    if(max%2 == 0) /*oyunda boyutu tek ve cift olan disklerin kendilerine ozel patternlari var ornegin disk sayisi tek ise tek disklerin patterni(ornegin 3. veya 5.diskler) : 3, 2, 1 ve cift disklerin pattern i: 2, 3, 1 disk sayisi cift oldugunda ise tam tersi, siradaki de bu disklerin gidecegi bir sonraki stacki ifade eden degisken*/
                    {
                        if(max_index == 1) siradaki = 0;
                        if(max_index == 2) siradaki = 1;
                        if(max_index == 0) siradaki = 2;
                    }
                    else
                    {
                        if(max_index == 1) siradaki = 2;
                        if(max_index == 2) siradaki = 0;
                        if(max_index == 0) siradaki = 1;
                    }
                }
                else
                {
                    if(max%2 == 0)
                    {
                        if(max_index == 1) siradaki = 2;
                        if(max_index == 2) siradaki = 0;
                        if(max_index == 0) siradaki = 1;
                    }
                    else
                    {
                        if(max_index == 1) siradaki = 0;
                        if(max_index == 2) siradaki = 1;
                        if(max_index == 0) siradaki = 2;
                    }
                }
                if(towers[siradaki].array[(towers[siradaki].currentsize)-1]>towers[max_index].array[(towers[max_index].currentsize)-1] || towers[siradaki].array[(towers[siradaki].currentsize)-1] == 0)
                { /*92.satirdaki if in ikinci onermesindeki (|| nin sagindaki onerme) eger o stack bossa zaten koyabilirsin anlamina geliyor, yani ilk once buyuk mu diye kontrol ediyor eger buyukse bos mu diye kontrol ediyor bossa koyuyor diski */
                    son_duzenlenen = towers[max_index].array[(towers[max_index].currentsize)-1];
                    push(&towers[siradaki], towers[max_index].array[(towers[max_index].currentsize)-1]);
                    pop(&towers[max_index]);
                    printf("Move disk %d from %d to %d\n", max, max_index+1, siradaki+1);
                    break;
                }
            }
        }
    }
    
}

int main()
{/*fonksiyonumda elemanlari koymadan once her zaman baslarda birer sifir adinda eleman oluyor yani stacklerim 3 2 1 diye gidecegine her zaman 0 3 2 1 diye gidiyor sebebi : */
    int i, disk_number;     /*algoritmamda currentsize -1 kullaniyorum ama eleman bittiginde -1.elemana ulasmaya calistigi icin cop degerler cikiyor bu yuzden basta butun */
    stack *ptr;             /*stacklerde 0 var ardindan pushlari yapiyorum ve currentsizelar hep 1 den basliyor orn(baslangicta eger disk_number = 3 ise) : stack 1: 0, 3, 2, 1 ; stack 2: 0 ; stack 3: 0;*/
    printf("Please enter the number of disks..: "); /*109. satirda bahsettigim yerler 122.satir currentsize in birden baslamasi, 123. satirin disk_num+1 olmasi ve 120.satirda realloc yaparken disk_num+1 kadar yer actigim satirlar*/
    scanf("%d", &disk_number);
    ptr = init_return();
    if(init(ptr)) /*eger yer acilmamissa ptr = 0 dondureceginden ve bu da if(0) olcagindan if in icini boyle doldurdum hocam degisik olsun diye*/
    {
        for(i=0;i<3;i++)
        {
            ptr[i].array = (int *)calloc(sizeof(int), STACK_BLOCK_SIZE+1);
            if(disk_number>STACK_BLOCK_SIZE) /*REALLOC KISMI*/
            {
                ptr[i].array = realloc(ptr[i].array, disk_number+1); /*+1 yapma kismim yukarida bahsettigim bastaki sifirlarin olmasi currentsize -1 in hata vermesini engellemek*/
            }
            ptr[i].currentsize = 1;
            ptr[i].maxsize = disk_number+1;
        }
        for(i=0;i<disk_number;i++) /*ilk stackin icini "1". elemandan (0 degil) baslayarak 1 2 3 ... disk_number olmak uzere dolduruyorum*/
        {
            push(&(ptr[0]), disk_number-i);
        }
        game(disk_number, ptr); /*esas movelarin ifade edilecegi yer*/
    }
    return 0;
}
