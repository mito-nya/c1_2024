#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

void simeq(double *apt, double *bpt, int n){
    int i, j, k;

    for (k = 0; k < n; k++) {
        // スケーリング
        for (j = k + 1; j < n; j++) {
            *(apt + k * n + j) = *(apt + k * n + j) / *(apt + k * n + k);
        }
        *(bpt + k) = *(bpt + k) / *(apt + k * n + k);
        // 消去        
        for (i = 0; i < n; i++) {
            if (i != k) {
                for (j = k + 1; j < n; j++) {
                    *(apt + i * n + j) = *(apt + i * n + j) - *(apt + i * n + k) * *(apt + k * n + j);
                }
                *(bpt + i) = *(bpt + i) - *(apt + i * n + k) * *(bpt + k);
            }
        }
    }
}

void squ(int I, double *xpt, double *ypt, double *bpt){
    double sx, sy, sxx, sxy;
    sx=0.;
    sy=0.;
    sxx=0.;
    sxy=0.;
    for(int i=0;i<I;i++){
        sx+=*(xpt+i);
        sy+=*(ypt+i);
        sxx+=*(xpt+i)**(xpt+i);
        sxy+=*(xpt+i)**(ypt+i);
    }
    // printf("%e, %e, %e, %e\n", sx, sy, sxx, sxy);
    double A[2][2]={{I+0., sx}, {sx, sxx}};
    *(bpt+0)=sy;
    *(bpt+1)=sxy;
    // printf("%e, %e, %e, %e, %e, %e\n", A[0][0], A[0][1], A[1][0], A[1][1], bpt[0], bpt[1]);
    simeq(&A[0][0], &bpt[0], 2);
    // printf("%e, %e\n", bpt[0], bpt[1]);
    
}

int main(void){
    double x[3]={1., 2., 3.};
    double y[3]={0., 2., 4.};
    double a[2]={0., 0.};
    int I=3;

    squ(I, &x[0], &y[0], &a[0]);
    printf("%e, %e", a[0], a[1]);
    return 0;
}