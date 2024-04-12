#include <stdio.h>
#include <math.h>
#define N 4
double polynomial(double *apt, double x, int n){
    double fx;
    fx=apt[n];
    for(int i=n-1;i>=0;i--){
        fx=fx*x+apt[i];
    }
    return fx;
}
int main(void){
    double x=1.;
    static double a[N+1]={1., 2., 3., 4., 5.};
    double fx=polynomial(a, x, N);
    printf("%15.8e\n", fx);
    return 0;
}