#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265
#define diff 1.e-5

double f(double x){
    return log(x*x/(1-x));
}

void bisec(double z, double *xmin, double *xmax, double funcpt(double x)){
    double c=20.99-log(0.02*pow((1.+z), 1.5))-25050./(1.+z);
    // printf("%e, %e, ", z, c);
    while(*xmax-*xmin>diff){
        double x0=(*xmin+*xmax)/2.;
        if((funcpt(*xmin)-c)*(funcpt(x0)-c)<0){
            *xmax=x0;
        }else if((funcpt(*xmin)-c)*(funcpt(x0)-c)>0){
            *xmin=x0;
        }else{
            *xmin=x0;
            *xmax=x0;
        }
    }
}

int main(void){
    double zmin=0.;
    double zmax=5000.;
    int I=500;
    double dz=(zmax-zmin)/(I+0.);
    for(int i=0;i<I;i++){
        double xmin=1.e-300;
        double xmax=1.-(1.e-300);
        double z=zmin+i*dz;
        bisec(z, &xmin, &xmax, f);
        printf("%e, %e\n", z, xmin);
    }
    return 0;
}