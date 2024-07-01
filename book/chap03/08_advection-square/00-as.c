#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

double f(double x){
    if(fabs(x) < 0.2){
        return 1.;
    }else{
        return 0.;
    }
}

int main(void){
    double a=-0.5;       // 始点
    double b=0.5;        // 終点
    double c=1.;         // 伝播速度, ここを変える
    double dx=1./63;     // 空間刻みの幅
    double nu=0.7;       // CFL数
    double dt=nu*dx/c;   // 時間刻みの幅
    int I=(b-a)/dx+1;    // 空間ステップ数
    int N=1/dt;          // 時間ステップ数

    double u[I];         // 数値解を格納する配列
    double tmp[I];       // 一時的に格納

    // 初期条件の設定
    for(int i=0; i<I; i++){
        u[i]=f(a+i*dx);
        tmp[i]=u[i];
    }

    // ファイルの用意
    char filename[256];
    sprintf(filename, "out_00.data");
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