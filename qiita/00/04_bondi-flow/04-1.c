#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

double f(double x, double r, double l){
    return l*l/2./pow(r, 4.)/x/x+log(x)-1./r;
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
    double l=0. ;
    return 0;
}