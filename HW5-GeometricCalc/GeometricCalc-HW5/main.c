#include <stdio.h>
#include <math.h>

#define PI 3.14

enum Shapes
{
    zero,
    Triangle,
    Quadrilateral,
    Circle,
    Pyramid,
    Cylinder
};

enum Calculators
{
    sifir,
    Area,
    Perimeter,
    Volume
};

int ucgen_kontrol(double a, double b, double c) /*verilen kenarlarin ucgen olusturup olusturmadigini kontrol ediyor */
{
    int counter = 0; /*counter sonda 3 olmali*/
    if (fabs(b - c) < a && b + c > a)
        counter++;
    if (fabs(a - c) < b && a + c > b)
        counter++;
    if (fabs(b - a) < c && b + a > c)
        counter++;
    if (counter == 3)
        return 1;
    else
        return 0;
}

int quad_kontrol(double a, double b, double c, double d)
{
	double s = (a+b+c+d)/2;
	while(1)
	{
		if(s>a && s>b && s>c && s>d) return 1;
		else return 0;
	
	}
}

double kenar_alma(void) /*bu fonksiyonu sekillerin kenarlarini hatasiz almak icin yazdim her seferinde kontrol*/
{                       /*etmek yerine tek fonksiyonu surekli cagiriyorum kenar almak icin*/
    double side;        /*bu fonksiyona kenar alma yazdm ama herhangi bir deger aliyor ve char sa veya negatif*/
                        /*bir degerse hata veriyor, yani yaricap da alabilir yuksekliik de alabilir*/
    while (1)
    {
        if (scanf("%lf", &side) == 0 || side < 0)
        {
            printf("ERROR: please enter a valid entry\n");
            while ((getchar()) != '\n') ; /*buffer i temizlemek icin (eger kullanici string vs girerse diye)*/
        }
        else
        {
        	while ((getchar()) != '\n');
            return side;
        }
    }
}

int calc_triangle(int calc)
{
    double s,A,perim,a,b,c;
    switch (calc)
    {
        case Volume:
            printf("ERROR: you can not calculate the volume of a triangle. Please try again\n");
            break;
        case Area:
            while(1)
            {
                printf("Please enter three sides of triangle..: \n");
                a = kenar_alma();
                b = kenar_alma();
                c = kenar_alma();
                if(ucgen_kontrol(a,b,c) == 0)  printf("ERROR: please enter a valid triangle\n");
                else break; /*ucgen kenarlari uygunsa 1 dondurecek ve whiledan cikacak*/
            }
            s = (a+b+c)/2;
            A = sqrt(s*(s-a)*(s-b)*(s-c));
            printf("Area of triangle : %lf\n", A);
            break;
        case Perimeter:
            while(1)
            {
                printf("Please enter three sides of triangle..: \n");
                a = kenar_alma();
                b = kenar_alma();
                c = kenar_alma();
                if(ucgen_kontrol(a,b,c) == 0)  printf("ERROR: please enter a valid triangle\n");
                else break; /*ucgen kenarlari uygunsa 1 dondurecek ve whiledan cikacak*/
            }
            perim = a+b+c;
            printf("Perimeter of triangle : %lf\n", perim);
            break;
    }
    return 1;
}

int calc_quadrilateral(int calc)
{
    double A, s, a ,b ,c ,d, perim;
    switch (calc)
    {
        case Area:
        	while(1)
        	{
		        printf("please enter four sides of quadrilateral..: \n");
		        a = kenar_alma();
		        b = kenar_alma();
		        c = kenar_alma();
		        d = kenar_alma();
		        if(quad_kontrol(a, b, c, d) == 1) break;
		        else printf("ERROR : please enter a valid quadraliteral\n");
            }
          	s = (a+b+c+d)/2;
            A = sqrt((s-a)*(s-b)*(s-c)*(s-d));
            printf("Area of quadrilateral: %lf\n", A);
            break;
        case Perimeter:
        	while(1)
        	{
		        printf("please enter four sides of quadrilateral..: \n");
		        a = kenar_alma();
		        b = kenar_alma();
		        c = kenar_alma();
		        d = kenar_alma();
		        if(quad_kontrol(a, b, c, d) == 1) break;
		        else printf("ERROR : please enter a valid quadraliteral\n");
		    }
            perim = a+b+c+d;
            printf("Perimeter of quadrilateral..: %lf\n", perim);
            break;
        case Volume:
            printf("ERROR : you can not calculate the volume of quadrilateral. Please try again\n");
            break;
    }
    return 1;
}

int calc_circle(int calc)
{
    double A, r,perim;
    switch(calc)
    {
        case Area:
            printf("Please enter the radius of the circle..: \n");
            r = kenar_alma();
            A = (PI)*r*r;
            printf("Area of circle : %lf\n", A);
            break;

        case Perimeter:
            printf("Please enter the radius of the circle..: \n");
            r = kenar_alma();
            perim = 2*PI*r;
            printf("Perimeter of circle : %lf\n", perim);
            break;

        case Volume:
            printf("ERROR : you can not calculate of the volume of a circle. Please try again\n");
            break;
    }
    return 1;
}

int calc_pyramid(int calc)
{
    double a, h, BA, LA, A, V;
    switch (calc)
    {
        case Area:
            printf("Please enter the base side and height of a pyramid : \n");
            a = kenar_alma();
            h = kenar_alma();
            BA = a*a;
            LA = 2*a*h;
            A = BA + LA;
            printf("Base surface area of pyramid ..: %lf\n", BA);
            printf("Lateral surface area of pyramid..: %lf\n", LA);
            printf("Surface area of this pyramid..: %lf\n", A);
            break;

        case Perimeter:
            printf("ERROR : you can not calculate the perimeter of a pyramid\n");
            break;
        
        case Volume:
            printf("Please enter the base side and height of a pyramid : \n");
            a = kenar_alma();
            h = kenar_alma();
            V = (a*a*h)/3;
            printf("Volume of this pyramid..: %lf\n", V);
            break;
            
    }
    return 1;
}

int calc_cylinder(int calc)
{
    double BA, LA, A, V, r, h, perim;
    switch (calc)
    {
    case Area:
        printf("Please enter the radius and height of Cylinder..: \n");
        r = kenar_alma();
        h = kenar_alma();
        BA = (PI)*r*r;
        LA = 2*(PI)*r*h;
        A = BA + LA;
        printf("Base surface area of this cylinder..: %lf\n", BA);
        printf("Lateral surface area of this cylinder..: %lf\n", LA);
        printf("Surface area of this cylinder..: %lf\n", A);
        break;

    case Perimeter:
        printf("Please enter the radius and height of Cylinder..: \n");
        r = kenar_alma();
        h = kenar_alma();
        perim = 2*(PI)*r;
        printf("Perimeter of this cylinder ..: %lf\n", perim);
        break;
    
    case Volume:
        printf("Please enter the radius and height of Cylinder..: \n");
        r = kenar_alma();
        h = kenar_alma();
        V = 2*(PI)*r*(r + h);
        printf("Volume of this cylinder..: %lf\n", V);
        break;
    }
    return 1;
}

int select_shape(void)
{
    int shape;
   
    while (1)
    {
        printf("Select a shape to calculate\n\n1-Triangle\n2-Qaudrilateral\n3-Circle\n4-Pyramid\n5-Cylinder\n0-EXIT\n\n");
        printf("INPUT : ");
        if (scanf("%d", &shape) == 0 || !(shape == 0 || shape == 1 || shape == 2 || shape == 3 || shape == 4 || shape == 5))
        {
            printf("ERROR: please enter a valid number to select shape\n");
            while ((getchar()) != '\n'); /*buffer i temizlemek icin*/
        }
        else 
        {
        	while ((getchar()) != '\n');
        	return shape;
        }
    }
}

int select_calc(void)
{
    int calculator;
    while (1)
    {
        printf("Select calculator:\n\n1-Area\n2-Perimeter\n3-Volume\n0-EXIT\n");
        printf("INPUT : ");
        if (scanf("%d", &calculator) == 0 || !(calculator == 1 ||calculator == 2 ||calculator == 3 ||calculator == 0)) /*calculator 0 1 2 3 den farkli bir sayiysa*/
        {                            
            printf("ERROR: please enter a valid number to select calculator\n");
            while ((getchar()) != '\n'); /*buffer i temizlemek icin*/
        }
        else
        {
        	while ((getchar()) != '\n');
            return calculator;
        }
    }
}

int calculate(int select_shape_ptr(void), int select_calc_ptr(void))
{
    int shape, calc;
    do
    {
        shape = select_shape_ptr();
        if(shape == 0) break;
        calc = select_calc_ptr();
        if(calc == 0) break;
        switch (shape)
        {
        case Triangle:
            calc_triangle(calc);
            break;
        
        case Quadrilateral:
            calc_quadrilateral(calc);
            break;

        case Circle:
            calc_circle(calc);
            break;
        
        case Pyramid:
            calc_pyramid(calc);
            break;
        case Cylinder:
        	calc_cylinder(calc);
        	break;
        }
    } while(shape != 0 && calc != 0);
    return 1;
}

int main()
{
    calculate(select_shape,select_calc);
    return 0;
}
