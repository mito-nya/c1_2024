#include <stdio.h>
#define N 3

/* 連立一次方程式を解くための関数（ガウス・ジョルダンの消去法） */
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

int main(void)
{
    double a[N][N] = {{2.0, 1.0, 1.0},
                      {2.0, 3.0, 1.0},
                      {1.0, 1.0, 3.0}};
    double b[N] = {2.0, 4.0, -1.0};

    int i, j, k;

    simeq(a, b, N);

    for (k = 0; k < N; k++) {
        printf("x%d = %4.1lf\n", k, b[k]);
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%4.1lf", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}