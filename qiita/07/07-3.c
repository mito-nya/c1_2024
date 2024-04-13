#include <stdio.h>
#include <math.h>
#define PI 3.14159265

double f(double x, double y){
    return -y;
}

void RK4(double x, double *y, double h, double funcpt(double x, double y)){
    double k1, k2, k3, k4;
    double y1;
    k1=h*funcpt(x, *y);
    k2=h*funcpt(x+h/2., *y+k1/2.);
    k3=h*funcpt(x+h/2., *y+k2/2.);
    k4=h*funcpt(x+h, *y+k3);
    *y=*y+(k1+2.*k2+2.*k3+k4)/6.;
}

int main(void){
    double x, y, h, b;
    int i, imax;
    
    x=0.;
    y=1.;
    h=1e-2;
    imax=1/h+1;

    for(i=0;i<imax;i++){
        RK4(x, &y, h, f);
        x=x+h;
        printf("%d, %e, %e\n", i, x, y);
    }
    return 0;
}