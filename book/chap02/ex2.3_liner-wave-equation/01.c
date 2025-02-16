#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

double f(double x){
    return sin(x);
}

int main(void){
    double a=0.;       // 始点
    double b=2.*PI;    // 終点
    double c=-1.;      // 伝播速度, ここを変える
    double dx=1/20.;   // 空間刻みの幅
    double nu=1.0;     // CFL数
    double dt=nu*dx/c;   // 時間刻みの幅
    int I=(b-a)/dx+1;  // 空間ステップ数
    int N=1001;        // 時間ステップ数

    double u[I];       // 数値解を格納する配列
    double tmp[I];     // 一時的に格納

    // 初期条件の設定
    for(int i=0; i<I; i++){
        u[i]=f(a+i*dx);
        tmp[i]=u[i];
    }

    for(int step=0; step<N+2; step++){
        // tが10 stepごとにファイル出力
        if(step%10==0){
            // ファイルの用意
            char filename[256];
            sprintf(filename, "out_minus_%02d_%04d.data", (int)((nu+0.01)*10.), step);
            FILE *file = fopen(filename, "w");
            if(file == NULL){
                perror("Failed to open file. ");
                exit(1);
            }

            // ファイルへの書き込み
            for(int i=0; i<I; i++){
                fprintf(file, "%e, %e\n", a+i*dx, u[i]);
            }

            fclose(file);
        }

        // 解くパート
        for(int i=0; i<I; i++){
            int j=(i+I-1)%I;
            int k=(i+I)%I;
            int l=(i+I+1)%I;

            tmp[k]=u[k]-nu/2.*(u[l]-u[j])+fabs(nu)/2.*(u[j]-2.*u[k]+u[l]);
        }
        for(int i=0; i<I; i++) u[i]=tmp[i];
    }
    return 0;
}