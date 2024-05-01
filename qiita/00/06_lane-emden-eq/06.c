#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265
#define index 5.

double f(int i, double x, double *y){
    if(i==0) return -y[1]/x/x;
    if(i==1) return x*x*pow(y[0], index);
}

void RK4(double x, double *y, int n, double h, double funcpt(int i, double x, double *y)){
    double *k1pt, *k2pt, *k3pt, *k4pt, *work;
    int i;

    // 記憶領域の確保
    k1pt = (double *) malloc(n*8);
    k2pt = (double *) malloc(n*8);
    k3pt = (double *) malloc(n*8);
    k4pt = (double *) malloc(n*8);
    work = (double *) malloc(n*8);
    for (i = 0; i < n; i++) k1pt[i] = h * funcpt(i, x, y);
    for (i = 0; i < n; i++) work[i] = y[i] + k1pt[i] / 2.0;
    for (i = 0; i < n; i++) k2pt[i] = h * funcpt(i, x + h / 2.0, work);
    for (i = 0; i < n; i++) work[i] = y[i] + k2pt[i] / 2.0;
    for (i = 0; i < n; i++) k3pt[i] = h * funcpt(i, x + h / 2.0, work);
    for (i = 0; i < n; i++) work[i] = y[i] + k3pt[i];
    for (i = 0; i < n; i++) k4pt[i] = h * funcpt(i, x + h, work);
    for (i = 0; i < n; i++) y[i] = y[i] + (k1pt[i] + 2.0 * k2pt[i] + 2.0 * k3pt[i] + k4pt[i]) / 6.0;
    // メモリの解放
    free(k1pt);
    free(k2pt);
    free(k3pt);
    free(k4pt);
    free(work);
}

int main(void){
    double x, y[2], h;
    int n, imax;

    h=1.e-2;
    imax=10./h+1;
    x=h;
    n=2;
    y[0]=1-h*h/6.+index*pow(h, 4.)/120.;
    y[1]=h*h*h/3.-index*pow(h, 5.)/30.;
    double rmax=-1.;

    // for(int i=0;i<10*imax;i++){
    //     RK4(x, &y[0], n, h, &f);
    //     x=x+h;
    //     if(y[0]<h && rmax==-1.){
    //         rmax=x;
    //         break;
    //     }
    // }
    
    y[0]=1-h*h/6.+index*pow(h, 4.)/120.;
    y[1]=h*h*h/3.-index*pow(h, 5.)/30.;

    // printf("%e, %e, %e, %e, %e\n", x, y[0], y[1], x/rmax, pow(y[0], index));

    printf("%e, %e, %e\n", x, y[0], y[1]);


    for(int i=0;i<imax;i++){
        RK4(x, &y[0], n, h, &f);
        x=x+h;
        // printf("%e, %e, %e, %e, %e\n", x, y[0], y[1], x/rmax, pow(y[0], index));
        printf("%e, %e, %e\n", x, y[0], y[1]);
    }

    return 0;
}