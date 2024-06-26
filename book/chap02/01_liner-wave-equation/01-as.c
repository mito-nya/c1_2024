// 解析解を出力する用

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
    double dx=1.e-2;     // 空間刻みの幅
    double nu=0.8;       // CFL数
    double dt=nu*1./c;   // 時間刻みの幅
    int I=(b-a)/dx+1;    // 空間ステップ数
    int N=5;             // 時間ステップ数

    double u[I];         // 数値解を格納する配列

    // 初期条件の設定
    for(int i=0; i<I; i++){
        u[i]=f(a+i*dx-c*4*dt);
    }

    // ファイルの用意
    char filename[256];
    sprintf(filename, "as_08.data");
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