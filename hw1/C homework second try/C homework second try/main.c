//
//  main.c
//  C homework second try
//
//  Created by Mehmet Soner Korucu on 12.11.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* double Function (double a, double x)
{
    double equation;
    equation = (x*x)-a;
    return equation;
}

double SearchMethod (double a)
{
    double endPoint = a;
    double startPoint = 0;
    double x1;
    double x2;
    double difference = 0.0001;
    while (1) {
        
        double interval = (endPoint - startPoint)/ 10;
        for (x2 = endPoint; Function(x2, a)*Function(startPoint, a) < interval; x2-= difference)
        {
            endPoint = x2;
        }
        for (x1 = startPoint; Function(x1, a)*Function(endPoint, a)< interval; x1+= difference)
        {
            startPoint = x1;
        }
        if (Function(x2, a) < difference && difference>Function(x1, a))
        {
            double root = x2;
            
            return root;
        }
    }
    

    
}
int main()
{
 double input;
 double result;
 printf("give an input:\t");
 scanf("%lf",&input);
 result = SearchMethod(input);
 printf("%f",result);

}

*/


double equation(double x, double a){
    double equation = (x*x)+a;
    return equation;
}
double SearchMethod(double a){
    double endPoint = a;
    double startPoint = 0;
    double x2;
    double x1;
    double root;
    double difference = 0.0001;
    while(1){
        double interval = (endPoint - startPoint)/10;
        for (x2= endPoint; equation(x2, a) * equation(startPoint, a)<0;x2 -= interval){
            endPoint = x2;
        }
        for (x1 = startPoint;equation(x1, a)*equation(endPoint,a)<0;x1 +=interval){
            startPoint = x1;
        }
        if (equation(x2, a) < difference && difference > equation(x1, a)){
            root = x2;
            return root;
            break;
            
        }
    }
}
int main(){
    double input;
    printf("write a number: ");
    scanf("%lf",&input);
    double SM = SearchMethod(input);
    printf("%f",SM);
    return 0;
}



