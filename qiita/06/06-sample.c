#include <stdio.h>
#include <math.h>

double f(double x);
double df(double x);
void newton(double *x0, double eps, int *nitr);

int main(void)
{
    static double eps = 1.0e-8;
    double x0;
    int nitr;

    printf("初期値の入力: x0 = ");
    scanf("%lf", &x0);

    newton(&x0, eps, &nitr);

    printf("number of iterations: %3d\n", nitr);
    printf("solution: x = %15.8e\n", x0);

    return 0;
}

double f(double x)
{
    return x- cos(x);
}

double df(double x)
{
    return 1.0 + sin(x);
}

/* 非線形方程式を解くための関数（ニュートン・ラフソン法）*/
void newton(double *x0, double eps, int *nitr)
{
    int maxitr;
    double x1, dx;

    maxitr = 10;
    *nitr = 0;

    do {
        *nitr = *nitr + 1;
        x1 = *x0 - f(*x0) / df(*x0);

        if (*nitr >= maxitr) {
            *x0 = x1;
            printf("!!!!!!!!!!!!!!!\n");
            printf("!not converged!\n");
            printf("!!!!!!!!!!!!!!!\n");
            return;
        }
        dx = fabs((x1 - *x0) / x1);
        *x0 = x1;
    } while(dx > eps);
}
