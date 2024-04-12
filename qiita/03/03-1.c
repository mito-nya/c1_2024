#include <stdio.h>
#include <math.h>

int main(void){
    int i;
    float a1=1.e7;
    float a2=1.e7;
    float b1=1.;
    float b2=.1;
    for (i = 0; i<10000;i++){
        a1=a1+b1;
        a2=a2+b2;
    }
    printf("a1=%6.0f\n", a1);
    printf("a2=%6.0f\n", a2);
    return 0;
}