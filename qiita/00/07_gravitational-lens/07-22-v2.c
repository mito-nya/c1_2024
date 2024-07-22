#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

#define c 1.
#define G 1.
#define M 1.


double f(int i, double x, double *y){
    if(i==0) return y[1];
    if(i==1) return -y[0]+(3*G*M/c/c)*y[0]*y[0];
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
    int n, imax, times;
    double rg=2.*G*M/c/c; // シュバルツシルト半径をとりあえず定義しておく

    h=3.e-3;
    imax=2.*PI/h+1;
    n=2;
    
    double xx=10.;
    double yy=7.;
    double r0=pow(xx*xx+yy*yy, .5);
    double phi=atan(yy/xx);
    double phimax=4*PI;
    double dphi=(phimax-phi)/(imax+0.);
    y[0]=1./r0;
    y[1]=pow(1.-rg/r0, .5)/r0/tan(phi);

    double ans[imax][2];
    ans[0][0]=phi;
    ans[0][1]=1./y[0];
    for(int i=1; i<1+imax; i++){
        RK4(phi, &y[0], n, dphi, &f);
        phi+=dphi;
        ans[i][0]=phi;
        ans[i][1]=1./y[0];
        if(y[0]>.5 || y[0]<0.03){
            for(int k=i+1;k<1+imax; k++){
                ans[k][0]=ans[k-1][0];
                ans[k][1]=ans[k-1][1];
            }
            break;
        }
        // printf("%e, %e, ", phi, y[0]);
    }
    // printf("\n");


    for(int i=0;i<1+imax;i++){
        double r=ans[i][0];
        double phi=ans[i][1];
        printf("%e, %e\n", r*cos(phi), r*sin(phi));
    }

    return 0;
}