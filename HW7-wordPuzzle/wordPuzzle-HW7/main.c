#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

char riddle[15][15]; /* dizimi global tanimliyorum*/
char words[51][100]; /*filedaki kelimeleri bastan bir diziye atip diziyle islem yapacagim surekli okumamak icin*/
int length[50]; /*butun kelimelerin boyutunu buraya atiyorum surekli strlen kullanip programi yavaslatmamak icin*/

enum directions
{
    north, northeast, east, southeast, south, southwest, west, northwest
};

int random_sayi(int mod)
{
    return rand()%mod;
}

void fill_the_words_array()  /*words arrayimi dolduracagim*/
{
    int i = 0;
    FILE *fileoku = fopen("wordlist.txt", "r");
    while(!feof(fileoku))
    {
        fscanf(fileoku, "%s", words[i]);
        i++;
    }
    fclose(fileoku);
}

void generate_length_array() /*her kelimenin uzunlugunu bir diziye atacagim ki her seferinde strlen yapmak zorunda kalmayayim*/
{
    int i;
    for(i=0;i<50;i++)
        length[i] = strlen(words[i]);
}

void fill_with_space()
{
    int i, j;
    for(i=0;i<15;i++)
        for(j=0;j<15;j++) 
            riddle[i][j] = ' ';
}

void print_array()
{
    int i,j;
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
            printf("%c ", riddle[i][j]);
        printf("\n");
    }
}

int is_it_valid_for_writing(int direction, int word, int column, int row) /*yazmak icin uygun mu diye bakiyor, daha once diziyi space le doldurmustuk*/
{
    int i;
    if(direction == north)
    {
        if(row-length[word]<0) return 0;
        for(i=0;i<length[word];i++) 
            if(riddle[row-i][column] != ' ') return 0;
    }
    else if(direction == northeast)
    {
        if(row-length[word]<0 || column+length[word]>14) return 0;
        for(i=0;i<length[word];i++) 
            if(riddle[row-i][column+i] != ' ') return 0;
    }
    else if(direction == east)
    {
        if(column+length[word]>14) return 0;
        for(i=0;i<length[word];i++) 
            if(riddle[row][column+i] != ' ') return 0;
    }
    else if(direction == southeast)
    {
        if(row+length[word]>14 || column+length[word]>14) return 0;
        for(i=0;i<length[word];i++) 
            if(riddle[row+i][column+i] != ' ') return 0;
    }
    else if(direction == south)
    {
        if(row+length[word]>14) return 0;
        for(i=0;i<length[word];i++)
            if(riddle[row+i][column] != ' ') return 0;
    }
    else if(direction == southwest)
    {
        if(row+length[word]>14 || column-length[word]<0) return 0;
        for(i=0;i<length[word];i++) 
            if(riddle[row+i][column-i] != ' ') return 0;
    }
    else if(direction == west)
    {
        if(column-length[word]<0) return 0;
        for(i=0;i<length[word];i++) 
            if(riddle[row][column-i] != ' ') return 0;
    }
    else if(direction == northwest)
    {
        if(row-length[word]<0 || column-length[word]<0) return 0;
        for(i=0;i<length[word];i++) 
            if(riddle[row-i][column-i] != ' ') return 0;
    }
    return 1;
}

void fill_the_array(int direction, int word, int column, int row)
{
    int i;
    if(direction == north)
    {
        for(i=0;i<length[word];i++) 
            riddle[row-i][column] = words[word][i];
    }
    else if(direction == northeast)
    {
        for(i=0;i<length[word];i++) 
            riddle[row-i][column+i] = words[word][i];
    }
    else if(direction == east)
    {
        for(i=0;i<length[word];i++) 
            riddle[row][column+i] = words[word][i];
    }
    else if(direction == southeast)
    {
        for(i=0;i<length[word];i++) 
            riddle[row+i][column+i] = words[word][i];
    }
    else if(direction == south)
    {
        for(i=0;i<length[word];i++)
            riddle[row+i][column] = words[word][i];
    }
    else if(direction == southwest)
    {
        for(i=0;i<length[word];i++) 
            riddle[row+i][column-i] = words[word][i];
    }
    else if(direction == west)
    {
        for(i=0;i<length[word];i++) 
            riddle[row][column-i] = words[word][i];
    }
    else if(direction == northwest)
    {
        for(i=0;i<length[word];i++) 
            riddle[row-i][column-i] = words[word][i];
    }
}

void fill_riddle_randomly()
{
    int i, j;
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(riddle[i][j] == ' ')
                riddle[i][j] = 'a' + random_sayi(26);
        }
    }
}

void generate_the_riddle()
{
    int direction, word, column, row, i;
    for(i=0;i<7;i++)
    {
        do
        {
            direction = random_sayi(8);
            //printf("direction = %d\n", direction);
            word = random_sayi(50);
            column = random_sayi(15);
            row = random_sayi(15);

        }while (!is_it_valid_for_writing(direction, word, column, row));
        printf("word = %s\n", words[word]);
        printf("x = %d\n", column);
        printf("y = %d\n", row);
        fill_the_array(direction, word, column, row);
    }
}
//    north, northeast, east, southeast, south, southwest, west, northwest

int printX(char word[], int x, int y) /*prints X on the array*/
{   
    int dirx, diry, i, j, len, flag, counter;
    len = strlen(word);
    for(i=0;i<8;i++)
    {
        counter = 0;
        flag = 0;
        if(i==north && y-len>=0) 
        {
            dirx = 0;
            diry = -1;
        }
        else if(i==northeast && y-len>=0 && x+len<=14)
        {
            dirx = 1;
            diry = -1;
        }
        else if(i==east && x+len<=14)
        {
            dirx = 1;
            diry = 0;
        }
        else if(i==southeast && x+len<=14 && y+len<=14)
        {
            dirx = 1;
            diry = 1;
        }
        else if(i==south && y+len<=14)
        {
            dirx = 0;
            diry = 1;
        }
        else if(i==southwest && x-len>=0 && y+len<=14)
        {
            dirx = -1;
            diry = 1;
        }
        else if(i==west && x-len>=0)
        {
            dirx = -1;
            diry = 0;
        }
        else if(i==northwest && x-len>=0 && y-len>=0)
        {
            dirx = -1;
            diry = -1;
        }
        else {flag = 1;}
        if(flag!=1)
        {
            for(j=0;j<len;j++)
            {
                if(word[j] == riddle[y+j*diry][x+j*dirx]) counter++;
            }
        }
        if(counter == len)
        {
            for(j=0;j<len;j++)
            {
                riddle[y+j*diry][x+j*dirx] = 'X';
            }
            return 1;
        }
    }
    return 0;
}

void game()
{
    int x, y, point = 0, choice = 3, i, flag=0;
    char word[10];
    while(choice>0 && point<14)
    {
    	printf("Please enter the word you've found.. (if you want to quit enter :q command) ..: ");
        scanf("%s", word);
        if(word[0] == ':' && word[1] == 'q') break;
        printf("Please enter the x coordinates..: ");
        scanf("%d", &x);
        printf("Please enter the y coordinates..: ");
        scanf("%d", &y);
        
        for(i=0;i<50;i++)
        {
        	if(!strcmp(words[i], word)) flag = 1;
        }

        if(printX(word, x, y) && flag == 1)
        {
            point += 2;
            printf("Congratulations! You've founded the word! You've got 2 points. Your total points : %d\n", point);
        }
        else
        {
            choice--;
            printf("Unfortunately, you couldn't find the word. You have %d options left to choose\n", choice);
        }
        print_array();
        if(point == 14) printf("Congrutalitions!! you've won the game");
        if(choice == 0) printf("Unfortunetely, Game is Over\n");
    } 
}


int main()
{
    srand(time(NULL));

    fill_the_words_array();
    generate_length_array();
    fill_with_space();

    printf("\n\nTHE PURE FORM OF THE PUZZLE BEFORE IT IS FILLED\n\n");
    generate_the_riddle();
    print_array();
    fill_riddle_randomly();
    printf("\n\nTHE STATE OF THE PUZZLE AFTER IT HAS BEEN FILLED.\n\n");
    print_array();
    game();

    return 0;
}
