#include <stdio.h>
#include <math.h>

int calc(float a, float b, float c){
    float diff=1e-5;
    float D=b*b-4.*a*c;
    float x1, x2, re, im;
    if(abs(a-0)<diff){
        printf("ERROR: a=0\n");
        return 0;
    }else if(D>0){
        if(b>=0){
            x2=(-b-sqrtf(D))/(2.*a);
            x1=c/a/x2;
        }else{
            x1=(-b+sqrtf(D))/(2.*a);
            x2=c/a/x1;
        }
        printf("%15.8e\n%15.8e\n", x1, x2);
    }else if(D<0){
        re=-b/2./a;
        im=sqrtf(-D)/2./a;
        printf("%15.8e %15.8e i\n%15.8e %15.8e i\n", re, im, re, -im);
    }else{
        x1=-b/2./a;
        printf("%15.8e\n", x1);
    }
}

int main(void){
    float a, b, c;
    float D, x1, x2;
    printf("a, b, c?: \n");
    scanf("%f%f%f", &a, &b, &c);
    calc(a, b, c);
    return 0;
}