#include <stdio.h>
#include <math.h>
#define PI 3.14159265

double f(double x, double y){
    return sin(x)+cos(y);
}

void RK2(double x, double *y, double h, double b, double funcpt(double x, double y)){
    double k1, k2;
    double y1;
    k1=h*funcpt(x, *y);
    y1=*y+k1/2./b;
    k2=h*funcpt(x+h/2./b, y1);
    *y=*y+(1.-b)*k1+b*k2;
}

int main(void){
    double x, y, h, b;
    int i, imax;
    
    x=0.;
    y=0.;
    h=1e-2;
    imax=2*PI/h+1;
    b=.5;

    for(i=0;i<imax;i++){
        RK2(x, &y, h, b, f);
        x=x+h;
        printf("%d, %e, %e\n", i, x, y);
    }
    return 0;
}