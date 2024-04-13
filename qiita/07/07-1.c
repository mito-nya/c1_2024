#include <stdio.h>
#include <math.h>

double f(double x, double y){
    return -y;
}

void Euler(double x, double *y, double h, double funcpt(double x, double y)){
    *y=*y+h*funcpt(x, *y);
}

int main(void){
    double x, y, h;
    int i, imax;
    
    x=0.;
    y=1.;
    h=1e-2;
    imax=1./h+1;

    for(i=0;i<imax;i++){
        Euler(x, &y, h, f);
        x=x+h;
        printf("%d %e %e\n", i, x, y);
    }
    return 0;
}