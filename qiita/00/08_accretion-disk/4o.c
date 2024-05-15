#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double x){
    if(0.4 < x && x < 0.6){
        return 1.0;
    }else{
        return 0.0;
    }
}

void expli(double a, double dx, int I, double dt, int N, double *upt, double (*funcpt)(double)) {
    // 初期値の設定
    for (int i = 0; i < I; i++) {
        *(upt + i) = funcpt(a + i * dx);
    }

    // 時間発展を計算
    for (int n = 1; n < N; n++) {
        // 境界条件
        *(upt + n * I + 0) = 0.0;
        *(upt + n * I + I - 1) = 0.0;

        // 間を埋める
        for (int j = 1; j < I - 1; j++) {
            double b = dt / (dx * dx * dx);
            *(upt + n * I + j) = *(upt + (n - 1) * I + j) +
                b / (j * j * j) * ((j + 1) * *(upt + (n - 1) * I + j + 1) -
                                   2 * j * *(upt + (n - 1) * I + j) +
                                   (j - 1) * *(upt + (n - 1) * I + j - 1));
        }
    }
}

void out(double a, double dx, int I, int N, double *upt){
    for(int i=0; i<I; i++){
        printf("%e, ", a + i * dx);
        for(int j=0; j<N-1; j++){
            printf("%e, ", i * dx * *(upt + j * I + i)); // 角運動量
        }
        printf("%e\n", i * dx * *(upt + (N-1) * I + i)); // 角運動量
    }
}

void out1(double a, double dx, int I, int N, double *upt){
    for(int i=0; i<I; i++){
        printf("%e, ", a + i * dx);
        for(int j=0; j<N-1; j++){
            printf("%e, ", *(upt + j * I + i)); // 角運動量
        }
        printf("%e\n", *(upt + (N-1) * I + i)); // 角運動量
    }
}

int main(void){
    int I = 100;
    int N = 1000;
    double a = 0.0;
    double b = 1.0;
    double dt = 1.e-5;
    double dx = (b - a) / I;
    double *u = (double *)malloc(I * N * sizeof(double));

    if(u == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    expli(a, dx, I, dt, N, u, f);
    out(a, dx, I, N, u);

    free(u);
    return 0;
}
