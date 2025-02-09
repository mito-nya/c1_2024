#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#define PI 3.14159265

bool prime(int n){
    if(n < 2) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;
    for(int i = 3; i <= sqrt(n); i += 2){
        if(n % i == 0) return false;
    }
    return true;
}

int main(void){
    for(int i=10001; i<100000; i++){
        if(prime(i)){
            printf("%d\n", i);
        }
    }
    return 0;
}