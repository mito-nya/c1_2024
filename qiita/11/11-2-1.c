// implicit

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

double f(double x){
    return exp(-1*(x-.5)*(x-.5)/.25);
}

/* 連立一次方程式を解くための関数（ガウス・ジョルダンの消去法） */
void simeq(double *apt, double *bpt, int n){
    int i, j, k;
    int ipivot, ip;
    double amax, atmp, btmp;
    for (k = 0; k < n; k++) {
        // 部分ピボット選択
        ipivot=k;
        amax=fabs(*(apt+k*n+k));
        for(ip=k+1;ip<n;ip++){
            if(amax<fabs(*(apt+ip*n+k))){
                ipivot=ip;
                amax=fabs(*(apt+ip*n+k));
            }
        }
        if (ipivot != k) {
            for (j = 0; j < n; j++) {
                atmp = *(apt + k * n + j);
                *(apt + k * n + j) = *(apt + ipivot * n + j);
                *(apt + ipivot * n + j) = atmp;
            }
            btmp = *(bpt + k);
            *(bpt + k) = *(bpt + ipivot);
            *(bpt + ipivot) = btmp;
        }
        
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

// 出力するだけ
void out(double a, double dx, int I, int N, double *upt){
    for(int i=0;i<I; i++){
        printf("%e, ", a+i*dx);
        for(int j=0; j<N-1; j++){
            printf("%e, ", *(upt+i*N+j));
        }
        printf("%e\n", *(upt+i*N+N-1));
    }
}

void debug(int M, int N, double *mpt){
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            printf("%e ", *(mpt+i*N+j));
        }
        printf("\n");
    }
    printf("\n");
}


int main(void){
    int I=100;
    int N=1000;
    double a=-1.;
    double b=2.;
    double dt=1.e-3;
    double dx=(b-a)/(I+0.);
    double A[I][I];

    // double L[I][I];
    // double U[I][I];
    // LU(I, &A[0][0], &L[0][0], &U[0][0]);

    // debug(I, I, &L[0][0]);
    // printf("\n");
    // debug(I, I, &U[0][0]);
    double bmat[I];
    double u[I][N];
    for(int i=0;i<I; i++){
        for(int j=0; j<N; j++){
            u[i][j]=0.;
        }
    }
    // solve(a, dx, dt, I, N, &L[0][0], &U[0][0], &u[0][0], f);
    
    for(int i=0; i<I; i++){
        bmat[i]=f(a+i*dx);
        u[i][0]=f(a+i*dx);
    }

    for(int t=1; t<N; t++){
        // Aの定義
        for(int i=0;i<I;i++){
            for(int j=0;j<I;j++){
                A[i][j]=0.;
            }
        }
        A[0][0]=dx*dx/dt;
        for(int i=1;i<I-1;i++){
            A[i][i-1]=-1.;
            A[i][i]=2.+dx*dx/dt;
            A[i][i+1]=-1.;
        }
        A[I-1][I-1]=dx*dx/dt;

        // debug(I, I, &A[0][0]);
        
        for(int i=0; i<I; i++){
            bmat[i]=dx*dx/dt *bmat[i];
        }
        // 解く
        simeq(&A[0][0], &bmat[0], I);
        // debug(I, N, &u[0][0]);
        for(int i=0; i<I; i++){
            u[i][t]=bmat[i];
        }
    }

    // simeq(a, dx, dt, I, N, &A[0][0], &bmat[0], &u[0][0], f);
    out(a, dx, I, N, &u[0][0]);

    // debug(I, I, &A[0][0]);
    return 0;
}

// int main(void){
//     double A[2][2]={{1., 2.}, {3., 1.}};
//     double L[2][2]={{0., 0.}, {0., 0.}};
//     double U[2][2]={{0., 0.}, {0., 0.}};
//     LU(2, &A[0][0], &L[0][0], &U[0][0]);
//     debug(2, 2, &L[0][0]);
//     printf("\n");
//     debug(2, 2, &U[0][0]);
// }