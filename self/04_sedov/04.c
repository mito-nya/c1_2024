#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265
#define diff 1.e-5

double func(double gamma, double a, double b, double c, double d, double e, double f, double g, double h, double x){
    return -b*c/a*x+d*e/f*pow(x, gamma)+c*g/a-h;
}

void bisec(double gamma, double a, double b, double c, double d, double e, double f, double g, double h, double *xmin, double *xmax, double funcpt(double gamma, double a, double b, double c, double d, double e, double f, double g, double h, double x)){
    while(*xmax-*xmin>diff){
        double x0=(*xmin+*xmax)/2.;
        if((funcpt(gamma, a, b, c, d, e, f, g, h, *xmin))*(funcpt(gamma, a, b, c, d, e, f, g, h, x0))<0){
            *xmax=x0;
        }else if((funcpt(gamma, a, b, c, d, e, f, g, h, *xmin))*(funcpt(gamma, a, b, c, d, e, f, g, h, x0))>0){
            *xmin=x0;
        }else{
            *xmin=x0;
            *xmax=x0;
        }
    }
}

int main(void){
    int N=1000; // グリッド数
    double dl=1./N;
    double gamma=5./3;
    double rho=1.;
    double V=1.;
    double P=1.;
    printf("%e, %e, %e, %e\n", dl*N, rho, V, P);
    for(int i=N; i>1; i--){
        double a=i*rho;
        double b=V-gamma/2.;
        double c=i*(2*V-gamma-1);
        double d=i*(gamma-1)/rho;
        double e=(i+(5*(gamma+1)-4*V)/((gamma+1)-2*V));
        double f=i*pow(rho, gamma)/P;
        double g=3*V+i*rho*V+(V-(gamma+1)/2)*rho;
        double h=i*(2*V-gamma-1)*V+2*V*V-2.5*(gamma+1)*V+(gamma-1)*(i+2)*P/rho;
        double xmin=0.;
        double xmax=rho;
        bisec(gamma, a, b, c, d, e, f, g, h, &xmin, &xmax, func);
        rho=xmin;
        P=e/f*pow(rho, gamma);
        V=(-b*rho+g)/a;
        printf("%e, %e, %e, %e\n", dl*i, rho, V, P);
    }
    return 0;
}