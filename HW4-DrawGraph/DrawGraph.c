#include<stdio.h>

void yazdir(int a, int b, int c)
{
    FILE *fileptr = fopen("coefficients.txt", "w+");
    fprintf(fileptr, "%d\n%d\n%d", a, b, c);
    fclose(fileptr);
    printf("coefficents.txt file has been created\n");
}

int kontrol (int a, int b, int c, int j, int i) {
    if(j == (a*i*i) + (b*i) + c)
    {
        return 1;
    }
    return 0;
}

void red() {
  printf("\033[1;31m");
}
void blue() {
    printf("\033[0;34m");
}
void green() {
  printf("\033[0;32m");
}
void reset() {
  printf("\033[0m");
}

void drawGraph(int a, int b, int c) {
    int i, j;
    
    for(i=15;i>=-15;i--)
    {
        for(j=-55;j<=55;j++)
        {
            if(kontrol(a,b,c,j,i))
            {
                blue();
                printf("#");
            } 
            else if(j==-0)
            {
                if(i%5==0 && i!=0) 
                {
                    if(kontrol(a,b,c,j-2,i)!=1 && kontrol(a,b,c,j-3,i)!=1 )
                    {
                    red();
                    printf("\b\b\b\b%3d", i);
                    reset();
                    printf(" ");
                    }
                }
                green();
                printf("|");
            }
            else if(i==-1 && j%10==0)
            {
                if(kontrol(a,b,c,j,i)!=1 && kontrol(a,b,c,j-1,i)!=1 && kontrol(a,b,c,j-2,i)!=1)
                {
                red();
                printf("\b\b%2d", j);
                }
                else
                    printf(" ");
            }
            else if(i==0)
            {
                green();
                printf("-");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
        reset();
    }
}
void drawGraphFile(int a, int b, int c)
{
    int i, j;
    FILE *fileptr = fopen("graph.txt", "w+");
    
    
    for(i=15;i>=-15;i--)
    {
        for(j=-55;j<=55;j++)
        {
            if(kontrol(a,b,c,j,i))
            {
                
                fprintf(fileptr,"#");
            }
            else if(j==-0)
            {
                if(i%5==0 && i!=0) 
                {
                    if(kontrol(a,b,c,j-2,i)!=1 && kontrol(a,b,c,j-3,i)!=1 )
                    {
                        //fprintf(fileptr, " ");
                    }
                }
                fprintf(fileptr, "|");
            }
            else if(i==-1 && j%10==0)
            {
                if(kontrol(a,b,c,j,i)!=1 && kontrol(a,b,c,j-1,i)!=1 && kontrol(a,b,c,j-2,i)!=1)
                {
                    fprintf(fileptr, " ");
                }
                else
                    fprintf(fileptr, " ");
            }
            else if(i==0)
            {
            
                fprintf(fileptr, "-");
            }
            else
            {
                fprintf(fileptr, " ");
            }
        }
        fprintf(fileptr, "\n");   
    }
    fclose(fileptr);
}

int main()
{
    int selection, a, b, c, a_oku, b_oku, c_oku;
    do
    {
        printf("\nSelect an operation(1-4)..:\n");
        printf("\n1-Enter the coefficients\n2-Draw the graph\n3-Print the graph into a .txt file\n4-EXIT\n");
        scanf("%d", &selection);
        if(selection == 1)
        {
            printf("\nPlease enter the coefficients for the following equation: x=a*(y*y)+b*y+c\n");
            printf("a = ");
            scanf("%d", &a);
            printf("b = ");
            scanf("%d", &b);
            printf("c = ");
            scanf("%d", &c);
            yazdir(a,b,c);
        }
        else if(selection == 2)
        {
        	FILE *fileptr = fopen("coefficients.txt", "r+");
            if(fileptr == NULL)
            {
                printf("\nThere is not a file named coefficients.txt\n");
            }
            else
            {
        	fscanf(fileptr, "%d %d %d", &a_oku, &b_oku, &c_oku);
        	printf("\nCoefficients have been read from the coefficient file\n");
        	fclose(fileptr);
            drawGraph(a_oku, b_oku, c_oku);
            }
        }
        else if(selection == 3)
        {
            FILE *fileptr = fopen("coefficients.txt", "r+");
            if(fileptr == NULL)
            {
                printf("\nThere is not a file named coefficients.txt\n");
            }
            else
            {
        	fscanf(fileptr, "%d %d %d", &a_oku, &b_oku, &c_oku);
        	printf("\nCoefficients have been read from the coefficient file\n");
        	fclose(fileptr);
            drawGraphFile(a_oku, b_oku, c_oku);
            printf("\nThe graph has been written to graph.txt file\n");
            }
        }
        else if(selection != 4)
        {
        	printf("ERROR: Please enter a valid number for selection\n");
        }
    } while (selection != 4);
}
