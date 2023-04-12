#include<stdio.h>
#include<string.h>

int kullanici_sayisi = 0; /*program basta kullanicilari sayiyor daha sonra her eklediginde bu degiskeni artiriyor */
int borc_miktarlari[50]; /* kullanicilarin idlerine göre bu dizi her bir kullanicinin kac borcu oldugu bilgisini tutuyor*/

typedef union Person
{
    char name[50];
    char address[50];
    int phone;
} Person;

typedef union Loan
{
    float arr[3];  /* arr[0] = amount, arr[1] = interest_rate, arr[2] = period */
} Loan;

typedef struct BankAccount
{
    Person Customer;
    Loan Loans[3];
} BankAccount;

int how_many_user() /*line sayisiyla kullanici sayisi ayni oldugu icin line sayma fonksiyonu ile user sayiyorum*/
{
    FILE *fileptr = fopen("customers.txt", "r+");
    if(fileptr == NULL) return 0; /* eger dosya henuz olusturulmadiysa onceden olan datalari ekleyemeyecegimiz icin fonksiyondan cikiyor */
    int lines = 0;
    char ch;
    while(!feof(fileptr))
    {
        ch = fgetc(fileptr);
        if(ch == '\n')
        {
            lines++;
        }
    }
    fclose(fileptr);
    return lines;
}

void borclari_ekleme() /*baslangicta her kullanicinin borclarini tutan global bir dizimiz vardi, program kapanip acildiginda bunlar silinmisti bu bilgileri tekrar yerlestiriyorum*/
{
    int temp,i, temp3, counter = 0, j; /*butun temp degerler sadece istenen degerlerin atlanmasi ve esas okumak istedigim degere ulasmak icin var hicbirinin ozel baska bir gorevi yok*/
    float period, loan;
    char temp1[50], temp2[50], c, bos[150];
    FILE *fileptr = fopen("customers.txt", "r+");
    if(fileptr == NULL) return ;  /* eger dosya henuz olusturulmadiysa onceden olan datalari ekleyemeyecegimiz icin fonksiyondan cikiyor */
    for(i=0;i<kullanici_sayisi;i++)
    {
        fscanf(fileptr, "%d %s %s %d", &temp, temp1, temp2, &temp3);
        for(j=0;j<3;j++)
        {
            c = fgetc(fileptr);
            if(c != '*')
            {
                fscanf(fileptr, "%f %f ", &period, &loan);
                counter++;
            }
            else 
            {
                fgets(bos, 150, fileptr);
                break;
            }
        }
        borc_miktarlari[i] = counter;
        counter = 0;
    }
    fclose(fileptr);
}

void kullanicilari_ekleme(BankAccount *users) /*program kapandiktan sonra structtaki bilgiler yok oldugu icin tekrar structlari dolduruyorum*/
{
	int i, temp;
    FILE *fileptr = fopen("customers.txt", "r+");
    if(fileptr == NULL) return ;  /* eger dosya henuz olusturulmadiysa onceden olan datalari ekleyemeyecegimiz icin fonksiyondan cikiyor */
    for(i=0;i<kullanici_sayisi;i++)
    {
    	fscanf(fileptr, "%d %s", &temp, users[i].Customer.name);
        while(fgetc(fileptr) != '\n');
    }
    fclose(fileptr);
}


void listCustomers(BankAccount * users) /*structtaki bilgilere dayanarak kullaniciları printliyor*/
{
    int i;
    if(kullanici_sayisi == 0)
    {
    	printf("\nERROR : Listelenecek kullanici yok\n\n");
    	return ;
    }
    
    for(i=0;i<kullanici_sayisi;i++)
    {
        printf("ID = %d\nName = %s\n\n", i+1, users[i].Customer.name);
    }
}

void addCustomer (BankAccount *users) /*programa yeni bir kullanici ekliyorum*/
{
    char address[50];
    int phone;
    FILE *fileptr = fopen("customers.txt", "a+");
    printf("Please enter your name ..: ");
    scanf("%s", users[kullanici_sayisi].Customer.name);

    printf("Please enter your address..:");
    scanf("%s", address);
    printf("Please enter your phone number..:");
    if(scanf("%d", &phone)==0)
    {
    	printf("ERROR : uygun olmayan phone number girdiniz! \n\n");
    	while(getchar() != '\n');
    	return ;
    }
    fprintf(fileptr, "%d %s ", kullanici_sayisi, users[kullanici_sayisi].Customer.name); 
    fprintf(fileptr, "%s ", address); 
    fprintf(fileptr, "%d*                                \n", phone); /* ustune yazabilmek icin bosluk birakiyorum ki bilgilerin uzerine yazmasin */ 
    kullanici_sayisi++;
    fclose(fileptr);
}

float calculateLoan(float amount, float period, float interestRate) 
{
    if(period == 0.0) return amount;
    else return (interestRate+1)*calculateLoan(amount, period-1, interestRate);
}

void newLoan (BankAccount *users)
{
    int i, tut, yer, r[3], flag = 0; /*r = scanf fonksiyonlarinin return degerini tutuyor*/ /*flag girilen isimde bir kullanici var mi diye kontrol ediyor*/
    float loan = 0.0;
    char c;
    FILE *fileptr = fopen("customers.txt", "r+");
    if(fileptr == NULL) 
    {
		printf("\nERROR : Kayitli kullanici yok\n\n");
		return ;
    }
    char name[50], dosyadaki_name[50];
    printf("Loan eklemek istediginiz kullanicinin adini giriniz..:");
    scanf("%s", name);

    //KULLANICI BULMA (ID) (kullanicinin oldugu satira ulasiyorum)

    for(i=0;i<kullanici_sayisi;i++)
    {
        fscanf(fileptr, "%d ", &tut);
        fscanf(fileptr, "%s", dosyadaki_name);
        if(strcmp(dosyadaki_name, name) == 0) 
        {
        	flag = 1;
        	break;
        }
        else while(c = fgetc(fileptr)!='\n');
    }
    if(flag == 0)
    {
    	printf("\nERROR : Bu isimde bir kullanici bulunmamaktadir\n\n");
    	return ;
    }
    printf("Please enter the amount..:");

    // BORC HESAPLAMA ICIN GEREKLI DEGISKENLERI ALMA VE YERLESTIRME

    r[0] = scanf("%f", &(users[i].Loans[borc_miktarlari[i]].arr[0]));
    printf("Please enter the interest rate..:");
    r[1] = scanf("%f", &(users->Loans[borc_miktarlari[i]].arr[1]));
    printf("Please enter the period..:");
    r[2] = scanf("%f", &(users[i].Loans[borc_miktarlari[i]].arr[2]));
    if(r[0] == 0 || r[1] == 0 || r[2] == 0) 
    {
    	printf("\nERROR : Uygun degerler girmediniz\n\n");
    	while(getchar() != '\n');
    	return ;
    }
    loan = calculateLoan(users[i].Loans[borc_miktarlari[i]].arr[0], users[i].Loans[borc_miktarlari[i]].arr[2], users->Loans[borc_miktarlari[i]].arr[1]);

    /*DOSYAYA YAZDIRMA*/

    do
    {
        yer = ftell(fileptr);
        c = fgetc(fileptr);
    } while (c != '*');
    
    fseek(fileptr, yer, 0);
    fprintf(fileptr," %.1f ", users[i].Loans[borc_miktarlari[i]].arr[2]);
    fprintf(fileptr, " %.4f* ", loan);
    borc_miktarlari[i]++; /*buldugum kullaniciya borc ekledigim icin onun borc sayisini tutan degeri artiriyorum*/
    fclose(fileptr);
}

void getReport()
{
    int i, j, k, yer, borc_miktari = 0, selection, tut, phone;
    float id, period, loans[3], toplam = 0.0;
    char name[50], address[50], c, name_control[50], dosyadaki_name[50]; 
    FILE *fileptr = fopen("customers.txt", "r+");
    if(fileptr == NULL) 
    {
		printf("\nERROR : Goruntulenecek bilgi yok\n\n");
		return ;
    }
    printf("1- Loan\n2-Customers\nEnter your choice ..:");
    scanf("%d", &selection);
    for(i=0;i<3;i++) loans[i] = 0.0;
    if(selection == 1)
    {
        printf("Please enter the name you want to see its loans..:");
        scanf("%s", name_control);
        for(i=0;i<kullanici_sayisi;i++)
        {
            fscanf(fileptr, "%d ", &tut);
            fscanf(fileptr, "%s", dosyadaki_name);
            if(strcmp(dosyadaki_name, name_control) == 0) break;
            else while(c = fgetc(fileptr)!='\n');
        }
        if(borc_miktarlari[i] == 0) printf("There is not a loan for this user\n\n");
        fscanf(fileptr, "%s %d", address, &phone);
        for(j=0;j<borc_miktarlari[i];j++)
        {
            fscanf(fileptr, "%f", &period);
            fscanf(fileptr, "%f", &loans[j]);
            printf("\n=====================================\n");
            for(k=0;k<period;k++)
            {
                printf("%d. Month Installment : %.3f\n", k+1, loans[j]/period);
            }
            printf("\n=====================================\n");
        }
    }
    else if(selection == 2)
    {
        for(i=0;i<kullanici_sayisi;i++)
        {
        	printf("\n==========================================\n");
            for(k=0;k<3;k++) loans[k] = 0.0;
            fscanf(fileptr, "%f", &id);
            fscanf(fileptr, "%s", name);
            fscanf(fileptr, "%s", address);
            fscanf(fileptr, "%d", &phone);
            fscanf(fileptr, "%f", &period);
            printf("Customer ID = %d\nCustomer name = %s\nCustomer phone = %d\nCustomer address = %s\nLoans = [", i+1, name, phone, address);
            
            for(j=0;j<borc_miktarlari[i];j++)
            {
                fscanf(fileptr, "%f", &loans[j]);
                fscanf(fileptr, "%f", &period);
            }
            do
            {
                c = fgetc(fileptr);
            } while (c != '\n');
            
            printf("%.4f + %.4f + %.4f", loans[0], loans[1], loans[2]);
            toplam = loans[0] + loans[1] + loans[2];
            printf("] = %.4f\n", toplam);
            printf("\n==========================================\n");
            toplam = 0.0;
        }
    }
    else printf("You've entered unvalid number\n");
    
    fclose(fileptr);
}

int main()
{
    int selection, i;
    for(i=0;i<50;i++) borc_miktarlari[i] = 0;
    kullanici_sayisi += how_many_user();
    borclari_ekleme();
    BankAccount users[50];
    kullanicilari_ekleme(users);
    do
    {
        printf("=====================================\nWelcome to the bank management system\n=====================================\n"
        "1- List all the customers\n2- Add new customer\n3- New loan application\n4- Report menu\n5- Exit\nPlease enter your choice..:");
        scanf("%d", &selection);
        if(selection == 1)
        {
            listCustomers(users);
        }
        else if(selection == 2)
        {
            addCustomer(users);
        }
        else if(selection == 3)
        {
            newLoan(users);
        }
        else if(selection == 4)
        {
            getReport();
        }
        else if(selection != 5)
        {
            printf("Please enter an appropriate choice\n");
            while ((getchar()) != '\n') ; /*buffer i temizlemek icin */
        }
    } while(selection != 5);


    return 0;
}
