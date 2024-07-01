#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

double f(double x){
    return sin(2*PI*x);
}

double minmod(double x, double y){
    if(x*y > 0){
        if(fabs(x) < fabs(y)){
            return x;
        }else{
            return y;
        }
    }else{
        return 0;
    }
}

int main(void){
    double time=0.40;          // どこまで計算するか
    double a=-0.5;             // 始点
    double b=0.5;              // 終点
    double c=1.;               // 伝播速度, ここも変える
    double dx=1./63;           // 空間刻みの幅
    double nu=0.1;             // CFL数
    double dt=nu*dx/fabs(c);   // 時間刻みの幅
    int I=(int)((b-a)/dx)+1;   // 空間ステップ数
    int N=(int)(time/dt);      // 時間ステップ数
    double k=-1.;              // MUSCLのfree parameter

    double u[I];               // 数値解を格納する配列
    double tmp[I];             // 一時格納用

    // 初期条件の設定
    for(int i=0; i<I; i++){
        u[i]=f(a+i*dx);
        tmp[i]=u[i];
    }

    for(int step=0; step<N; step++){
        // 数値流束を求める
        double flux[I];
        for(int i=0; i<I; i++){
            // 周期境界条件を課す
            int im = (i+I-1)%I;
            int ip = (i+1)%I;
            int ipp = (i+2)%I;

            // 制限関数の導入
            double uL = u[i]+0.5*minmod(u[ip]-u[i], u[i]-u[im]);
            double uR = u[ip]-0.5*minmod(u[ip]-u[i], u[ipp]-u[ip]);

            flux[i] = (c*uL+c*uR)/2.-fabs(c)*(uR-uL)/2.;
        }

        // uを更新する
        for(int i=0; i<I; i++){
            int im = (i+I-1)%I;
            tmp[i] = u[i]-dt/dx*(flux[i]-flux[im]);
        }

        // 移す
        for(int i=0; i<I; i++){
            u[i]=tmp[i];
        }

        // デバッグ出力
        // if(step % 10 == 0){
        //     printf("Step %d:\n", step);
        //     for(int i=0; i<I; i++){
        //         printf("u[%d] = %f\n", i, u[i]);
        //     }
        // }
    }

    // ファイルの用意
    char filename[256];
    sprintf(filename, "out_limiter_%02d.data", (int)((time+0.003)*100));
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