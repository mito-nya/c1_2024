#include <stdio.h>
#include <math.h>

#define N 3
#define L 3
#define M 3

void matprd(float *xpt, float *ypt, float *zpt, int n, int l, int m){
    int i, j, k;
    for(i=0; i<n; i++){
        for(j=0;j<m;j++){
            *(zpt+i*m+j)=0.;
            for(k=0;k<l;k++){
                *(zpt+i*m+j)+=*(xpt+i*l+k) * *(ypt+k*n+j);
            }
        }
    }
}

void output(float *zpt, int n, int m){
    int i, j, k;
    for (i = 0; i < n; i++){
        for (j=0; j<m; j++){
            printf("%10.2f", *(zpt+i*m+j));
        }
        printf("\n");
    }
}

int main(void){
    static float a[N][L]={{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
    static float b[L][M]={{10., 11., 12.}, {13., 14., 15.}, {16., 17., 18.}};
    static float c[N][M];

    int i, j;

    matprd(&a[0][0], &b[0][0], &c[0][0], N, L, M);

    // for (i=0; i<N; i++){
    //     for (j=0; j<M; j++){
    //         printf("%10.2f", c[i][j]);
    //     }
    //     printf("\n");
    // }
    output(&c[0][0], N, M);
    return 0;
}