#include<stdio.h>
#include<math.h>
#define MAX 0x7fffffff
#define MIN -0x7fffffff-1

int sum(int n1, int n2, int flag)
{
	int i,sum=0;
	if(n1%2==flag) i=n1+2;
	else i=n1+1;
		while(i<n2)
		{
			sum = sum + i;
			i=i+2;
		}
	return sum;
}

int multi(int n1, int n2, int flag)
{
	int i, multi = 1;
	if(n1%2==flag) i=n1+2;
	else i=n1+1;
		while(i<n2)
		{
			multi = multi * i;
			i=i+2;
		}
	return multi;
}

int isprime(int prime)
{
	int i;
	for(i=2;i<=sqrt((double)prime);i++)
	{
		if(prime%i == 0) return i;
	}
	return 1;
}

void print_file()
{
    int tut;
    printf("Result.txt icindeki degerler..:\n");
    FILE *fileptr = fopen("result.txt", "r");
    while(!(feof(fileptr)))
    {
        fscanf(fileptr, "%d\n", &tut);
        printf("%d ", tut);
    }
    fclose(fileptr);
}

void write_file (int number)
{
    FILE *filep = fopen("result.txt", "a");
    fprintf(filep, "%d\n", number);
    fclose(filep);
}

void write_file2(int number) /*siralanmis sayilari temp dosyasina atmak icin yazdirma fonksiyonu */
{
    FILE *filep = fopen("siralanmis.txt", "a");
    fprintf(filep, "%d\n", number);
    fclose(filep);
}

void sort_file ()
{
    FILE *fileptr = fopen("result.txt", "a+");
    int min1, min2, min3, tut, sinir = MIN, flag= 1; /* 'flag' in amaci en sonda artik düzenlencek sayi kalmadiginda flag artmayacak ve dongu duracak*/
    while(flag != 0)								 /* 'sinir' amaci ilk ucluyu bulduktan sonra ikinci ucluyu ararken bir onceki ucludeki en buyuk...*/	
    {												 /* sayiyi sinir yapiyor ki sirada bulacagi uclu bir onceki ucluden kucuk olsun*/
        min1 = MAX;
        min2 = MAX;
        min3 = MAX;
        flag = 0;
        while(!(feof(fileptr)))
        {											 /* bu islemler tamamen kaydirmaya dayali, ornegin okudugumuz sayi min1den kucukse asagidaki...  */
            fscanf(fileptr, "%d\n", &tut);			 /* ikisini kaydiriyor bu if e girmezse asagidakine girerse bu da okudugumuz sayinin min1den buyuk...*/
            if(tut<min1 && tut>sinir)				 /* min 2 den kucuk oldugunu gösterir bu sefer min 2 yi kaydirmamiz gerekiyor */
            {
                min3 = min2;
                min2 = min1;
                min1 = tut;
                flag++;
            }
            else if(tut<min2 && tut>sinir)
            {
                min3 = min2;
                min2 = tut;
                flag++;
            }
            else if(tut<min3 && tut>sinir)
            {
                min3 = tut;
                flag++;
            }
        }
        if(min1 != MAX) write_file2(min1);
        if(min2 != MAX) write_file2(min2);
        if(min3 != MAX) write_file2(min3);
        rewind(fileptr);
        sinir = min3;
    }
    fclose(fileptr);
}

int main()
{
	int choice, i, n1, n2, flag, prime, kontrol, operation;
	while(1)
	{
		printf("\nSelect operation(1,2,3 or 4)..:");
		scanf("%d", &operation);
		if(operation == 1)
		{
			// PART 1
			printf("Please enter '0' for sum, '1' for multiplication..: ");
			scanf("%d", &choice);
			while(1)
			{
				printf("Please enter '0' to work on even numbers, '1' to work on odd numbers..:");
				scanf("%d", &flag);
				if(flag == 0 || flag == 1) break;
				printf("ERROR : Please enter a valid number\n");
			}
			printf("Please enter two different numbers..:");
			scanf("%d %d", &n1, &n2);
			printf("Number 1: %d\nNumber 2: %d\n", n1, n2);
			if(n1>n2)
			{
				int temp = n1; /* yer degistiriyorum ki n1 kucuk n2 buyuk olsun*/
				n1 = n2;
				n2 = temp;
			}
			switch(choice)
			{
				case 0:
					if(n1%2==flag) i=n1+2;
					else i=n1+1;
					while(i<n2)
					{
						printf("%d", i);
						if(i+2<n2) printf(" + ");
						i=i+2;
					}
					printf(" = %d", sum(n1, n2, flag));
					write_file(sum(n1, n2, flag));
					break;

				case 1:
					if(n1%2==flag) i=n1+2;
					else i=n1+1;
					while(i<n2)
					{
						printf("%d", i);
						if(i+2<n2) printf(" * ");
						i=i+2;
					}
					printf(" = %d", multi(n1, n2, flag));
					write_file(multi(n1, n2, flag));
					break;
                default:
                    printf("ERROR : please enter a valid number for function selection \n");
			}
		}
		else if(operation == 2)
		{
			//PART 2
			printf("Please enter an integer..:");
			scanf("%d", &prime);
			for(i=2;i<prime;i++)
			{
				kontrol = isprime(i);
				if(kontrol == 1) printf("%d is a prime number\n", i);
				else printf("%d is not a prime number, it is dividible by %d\n", i, kontrol);
			}
		}
		else if(operation == 3)
		{
            print_file();
		}
		else if(operation == 4) 
		{
			sort_file ();
			rename("siralanmis.txt","result.txt");
			print_file();
		}
        else printf("ERROR : Please enter a valid value for operation\n");
	}
}

