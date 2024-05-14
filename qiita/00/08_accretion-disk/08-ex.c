// explicit

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

// 2次元配列として, 空間の配列と時間の配列を持つようにする
void expli(double a, double dx, int I, double dt, int N, double *upt, double funcpt(double x)){
    // 初期値の設定
    for(int i=0;i<I;i++){
        *(upt+i)=funcpt(a+i*dx);
    }
    // 時間発展を計算していく
    for(int i=1;i<N;i++){
        // 境界条件
        *(upt+i*I+0)=*(upt+(i-1)*I+0);
        // 間を埋める
        double b=dt/pow(dx, 4.);
        for(int j=1;j<I-1;j++){
            *(upt+i*I+j) = *(upt+(i-1)*I+j) + (b/pow(j, 3.)) * ( (j+1) * *(upt+(i-1)*I+j+1) - 2*j* *(upt+(i-1)*I+j) + (j-1) * *(upt+(i-1)*I+j-1) );
        }
        // 境界条件
        *(upt+i*I+I-1)=*(upt+(i-1)*I+I-1);
    }
}

// 行と列と入れ替えて出力する？
void out(double a, double dx, int I, int N, double *upt){
    for(int i=0;i<I; i++){
        printf("%e, ", a+i*dx);
        for(int j=0; j<N-1; j++){
        // printf("%e, ", *(upt+j*I+i)); // 面密度
        printf("%e, ", i*dx* *(upt+j*I+i)); // 角運動量
        }
        // printf("%e\n", *(upt+(N-1)*I+i)); // 面密度
        printf("%e\n", i*dx* *(upt+(N-1)*I+i)); // 角運動量
    }
}
int main(void){
    int I=100;
    int N=1000;
    double a=0.;
    double b=1.;
    double dt=1.e-3;
    double dx=(b-a)/(I+0.);
    double u[I][N];
    expli(a, dx, I, dt, N, &u[0][0], f);
    out(a, dx, I, N, &u[0][0]);
    return 0;
}