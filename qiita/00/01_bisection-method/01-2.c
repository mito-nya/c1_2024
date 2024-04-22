#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265
#define diff 1.e-10

double f(double x){
    return x-2.*log(x+1.);
}

void bisec(double *xmin, double *xmax, double funcpt(double x)){
    double x0=(*xmin+*xmax)/2.;
    if(funcpt(*xmin)*funcpt(x0)<0) *xmax=x0;
    else if(funcpt(*xmin)*funcpt(x0)>0) *xmin=x0;
    else{
        *xmin=x0;
        *xmax=x0;
    }
}

int main(void){
    double xmin=1.;
    double xmax=4.;
    int count=0;
    while(xmax-xmin>diff){
        // printf("%d, %e, %e, %e, %e\n", count, xmin, xmax, f(xmin), f(xmax));
        bisec(&xmin, &xmax, f);
        count++;
    }
    printf("%d, %e, %e", count, xmin, f(xmin));
    return 0;
}