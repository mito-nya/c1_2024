#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

double f(double x){
    if(0.4 < x && x < 0.6){
        return 1.;
    }else{
        return 0.;
    }
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

int main(void){
    int I=100;
    int N=1000; // 時間のグリッド数
    double xmin=0.;
    double xmax=1.;
    double dt=1.e-3;
    double dx=(xmax-xmin)/(I+0.);
    double b=pow(dx, 4.)/dt;
    double A[I+1][I+1]; // Ax=bのA
    double bmat[I+1]; // Ax=bのb
    double u[I+1][N]; // 出力用

    for(int i=0;i<I+1; i++){
        for(int j=0; j<N; j++){
            u[i][j]=0.;
        }
    }
    
    for(int i=0; i<I+1; i++){
        bmat[i]=f(xmin+i*dx);
        u[i][0]=f(xmin+i*dx); // 面密度
        // u[i][0]=i*dx*f(xmin+i*dx); // 角運動量
    }

    for(int t=1; t<N; t++){
        // Aの定義
        for(int i=0;i<I+1;i++){
            for(int j=0;j<I+1;j++){
                A[i][j]=0.;
            }
        }
        A[0][0]=b;
        for(int i=1;i<I;i++){
            A[i][i-1]=-i+1;
            A[i][i]=pow(i, 3.)*b+2*i;
            A[i][i+1]=-i-1.;
        }
        A[I][I]=pow(I, 3.)*b;
        
        for(int i=1; i<I+1; i++){
            bmat[i]=pow(i, 3.)*b*bmat[i];
        }

        // 解く
        simeq(&A[0][0], &bmat[0], I+1);
        for(int i=0; i<I+1; i++){
            u[i][t]=bmat[i]; // 面密度
            // u[i][t]=i*dx*bmat[i]; // 角運動量
        }
    }

    out(xmin, dx, I, N, &u[0][0]);

    return 0;
}