#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265
#define E 2.718281828
#define diff 1.e-5

double f(double a, double x, double l){
    return l*l/2./pow(x, 4.)/a/a+log(a)-1./x;
}

void bisec(double *out, double *almin, double *almax, double x, double l, double funcpt(double a, double x, double l)){
    // int itr=0;
    // printf("check\n");
    while(*almax-*almin>diff){
        // printf("%d\n%e, %e, %e, %e\n", itr, *almin, *almax, f(*almin, x, l), f(*almax, x, l));
        // itr++;
        double x0=(*almin+*almax)/2.;
        if(funcpt(*almin, x, l)*funcpt(x0, x, l)<0) *almax=x0;
        else if(funcpt(*almin, x, l)*funcpt(x0, x, l)>0) *almin=x0;
        else{
            *almin=x0;
            *almax=x0;
        }
    }
    *out=*almin;
}

int main(void){
    double l=0.2;
    double xmin=1.e-1;
    double xmax=1.e1;
    int I=1000;
    double alpha=999.;
    double dx=(xmax-xmin)/(I+0.);

    // double x=1.;
    // double almin=1.;
    // double almax=10.;
    // bisec(&alpha, &almin, &almax, x, l, f);

    for(int i=0;i<I;i++){
        double x=xmin+i*dx;
        double almin=l/x/x; // 1に漸近する方の交点を求めるために
        double almax=alpha; // alphaは単調で1以上なので直前の値で制限できる
        bisec(&alpha, &almin, &almax, x, l, f);
        double v=l/x/x/alpha;
        printf("%e, %e, %e\n", x, alpha, v);
    }
    return 0;
}