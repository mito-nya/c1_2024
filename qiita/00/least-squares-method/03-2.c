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

void squ(int I, int N, double *xpt, double *ypt, double *Apt, double *bpt){
    // 係数行列Aの定義
    *(Apt+0*(N+1)+0)=I+0.;
    for(int i=1; i<2*N+1; i++){
        double tmp=0.;
        for(int k=0; k<I; k++){
            tmp += pow(*(xpt+k), i);
        }
        if(i<N+1){
            for(int j=0; j<i+1; j++){
                *(Apt+j*(N+1)+(i-j))=tmp;
            }
        }else{
            for(int j=i-N; j<i+1; j++){
                *(Apt+j*(N+1)+(i-j))=tmp;
            }
        }
        
    }
    // bの定義
    for(int i=0; i<N+1; i++){
        double tmp=0.;
        for(int j=0; j<I; j++){
            tmp += *(ypt+j)*pow(*(xpt+j), i);
        }
        *(bpt+i)=tmp;
    }
    simeq(Apt, bpt, N+1);
    // printf("%e, %e\n", bpt[0], bpt[1]);
}

int main(void){
    // もろもろ定義パート
    double x[5]={0., 1., 2., 3., 4.};
    double y[5]={1., 10., 49., 142., 313.};
    int I=5; // 点の個数
    int N=3; // N次式でfitting

    // 配列の初期化パート
    double b[N+1];
    for(int i=0;i<N+1;i++){
        b[i]=0.;
    }
    double A[N+1][N+1];
    for(int i=0;i<N+1;i++){
        for(int j=0; j<N+1; j++){
            A[i][j]=0.;
        }
    }

    // 解いて出力パート
    squ(I, N, &x[0], &y[0], &A[0][0], &b[0]);
    for(int i=0; i<N+1; i++) printf("a_%d=%e\n", i, b[i]);
    return 0;
}