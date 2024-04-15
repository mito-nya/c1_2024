#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265
#define E 2.718281828

double f(double x){
    return exp(x);
}

double daikei(double h, double a, double b, double *I, double funcpt(double x)){
    int N=(b-a)/h;
    for(int i=0;i<N;i++){
        *I=*I+(funcpt(i*h)+funcpt((i+1)*h))*h*.5;
    }
}

double simpson(double h, double a, double b, double *J, double funcpt(double x)){
    int N=(b-a)/h;
    for(int i=0;i<N;i++){
        *J=*J+(funcpt(i*h)+4.*funcpt((i+.5)*h)+funcpt((i+1)*h))*h/6.;
    }
}

int main(void){
    double h=1.e-4;
    double a=0.;
    double b=1.;
    double I, J;
    daikei(h, a, b, &I, f);
    simpson(h, a, b, &J, f);
    printf("value  : %e\ndaikei : %e\nsimpson: %e", E-1, I, J);
    return 0;
    // h=1.e-2
    // value  : 1.718282e+00
    // daikei : 1.691249e+00
    // simpson: 1.691234e+00
    //
    // h=1.e-3
    // value  : 1.718282e+00
    // daikei : 1.715565e+00
    // simpson: 1.715565e+00
    //
    // h=1.e-4
    // value  : 1.718282e+00
    // daikei : 1.718010e+00
    // simpson: 1.718010e+00

}