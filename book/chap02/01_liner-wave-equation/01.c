#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

double f(double x){
    if(x<10) return 1.;
    else return 0.;
}

int main(void){
    double a=0.;         // 始点
    double b=20.;        // 終点
    double c=1.;         // 伝播速度, ここも変える
    double dx=1.;        // 空間刻みの幅
    double nu=1.2;       // CFL数
    double dt=nu*dx/c;   // 時間刻みの幅
    int I=(b-a)/dx+1;    // 空間ステップ数
    int N=5;             // 時間ステップ数

    double u[I];         // 数値解を格納する配列
    double tmp[I];       // 一時格納用

    // 初期条件の設定
    for(int i=0; i<I; i++){
        u[i]=f(a+i*dx);
        tmp[i]=u[i];
    }

    for(int step=0; step<N; step++){
        // 境界条件
        tmp[0]=1.;

        // 解くパート
        for(int i=1; i<I-1; i++){
            // tmp[i]=(1+nu)*u[i]-nu*u[i+1];           // FTFS
            tmp[i]=nu*u[i-1]+(1-nu)*u[i];           // FTBS
            // tmp[i]=nu/2.*u[i-1]+u[i]-nu/2.*u[i+1];  // FTCS
        }

        // 境界条件
        tmp[I-1]=0.;

        // 移す
        for(int i=0; i<I; i++){
            u[i]=tmp[i];
        }
    }

    // ファイルの用意
    char filename[256];
    sprintf(filename, "out_FTBS_12.data");
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

    return 0;
}