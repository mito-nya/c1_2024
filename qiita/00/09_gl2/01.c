#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

// 定数の規格化
#define c 1.
#define G 1.
#define M 1.

// 解く微分方程式の定義
double f(int i, double x, double *y){
    if(i==0) return y[1];
    if(i==1) return -y[0]+(3*G*M/c/c)*y[0]*y[0];
}

// 4次のRunge-Kutta法
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
    double x, y[2];
    double rg = 2*G*M/c/c;

    int imax = 1000; // 計算する最大ステップ。適当に
    int n = 2; // Runge-Kuttaの式の本数

    // 初期値の設定
    double y0 = 5;
    double x0 = 10;
    double r0 = pow(x0*x0+y0*y0, .5);
    double phi = atan(y0/x0);
    y[0] = 1./r0;
    y[1] = pow(1.-rg/r0, .5)/r0/tan(phi);

    
    double phimax = 4*PI; // とりあえず大きめに設定
    double dphi = (phimax-phi)/imax; // 刻み幅

    while(y[0] < 0.5 && y[0] > 0.03){
        RK4(phi, &y[0], n, dphi, &f);
        phi += dphi;
        double r = 1./y[0];
        printf("%f, %f\n", r*cos(phi), r*sin(phi));
    }

    return 0;
}