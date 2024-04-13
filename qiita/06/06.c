#include <stdio.h>
#include <math.h>

double f(double x){
    return x-cos(x);
}
double df(double x){
    return 1.+sin(x);
}

void newton(double *x0, int *nitr){
    static double eps=1.e-8;
    int maxitr=100;
    double x1, dx;
    *nitr=0;
    do{
        *nitr=*nitr+1;
        x1=*x0-f(*x0)/df(*x0);
        if(*nitr>maxitr){
            *x0=x1;
            printf("%d, disconverge\n", *nitr);
            return;
        }
        dx=fabs((x1-*x0)/x1);
        printf("%d %15.8e\n", *nitr, dx);
        *x0=x1;
    } while (dx>eps);
}

int main(void){
    double x0;
    int nitr;
    printf("x0: ");
    scanf("%lf", &x0);
    newton(&x0, &nitr);
    printf("nitr: %3d\n", nitr);
    printf("x: %15.8e\n", x0);
    return 0;
}