#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

int find(int, int*);
void uni(int, int, int*);
void show(int, int*);
void connect(double, int, int, int, int, int, int*);
double mc_onestep(double, int);
int percolation_check(int, int*);
double mc_average(double, int, int);
void mc_all(int, int);
void out(int, int);

int main(void){
    srand(0);
    int L[3]={8, 16, 32};
    int num_samples = 10000;
    for(int i=0; i<3; i++) out(L[i], num_samples);
    return 0;
}

int find(int index, int *cluster){
    while(index != *(cluster+index)){
        index = *(cluster+index);
    }
    return index;
}

void uni(int index1, int index2, int *cluster){
    int c1 = find(index1, cluster);
    int c2 = find(index2, cluster);
    if(c1 < c2) *(cluster+c2)=c1;
    else *(cluster+c1)=c2;
}

void show(int L, int *cluster){
    for(int i=0; i<L; i++){
        for(int j=0; j<L; j++){
            int index=i*L+j;
            int c=find(index, cluster);
            printf("%02d ", c);
        }
        printf("\n");
    }
}

void connect(double p, int x1, int y1, int x2, int y2, int L, int *cluster){
    int i1=x1+y1*L;
    int i2=x2+y2*L;
    if( (double)rand()/RAND_MAX < p){
        uni(i1, i2, cluster);
    }
}

double mc_onestep(double p, int L){
    int N=L*L;
    int cluster[N];
    for(int i=0; i<N; i++) *(cluster+i) = i;

    for(int i=0; i<L-1; i++){
        for(int j=0; j<L-1; j++){
            connect(p, i, j, i+1, j, L, cluster);
            connect(p, i, j, i, j+1, L, cluster);
        }
    }

    for(int i=0; i<L-1; i++){
        connect(p, L-1, i, L-1, i+1, L, cluster); // 右端の接続
        connect(p, i, L-1, i+1, L-1, L, cluster); // 下端の接続
    }

    // show(L, cluster);

    if(percolation_check(L, cluster) == 1){
        // printf("Percolated\n\n");
        return 1.;
    }else{
        // printf("Not Percolated\n\n");
        return 0.;
    }
}

int percolation_check(int L, int *cluster){
    for(int i=0; i<L; i++){
        int c1=find(i, cluster);
        for(int j=0; j<L; j++){
            int c2=find(j+(L-1)*L, cluster);
            if(c1==c2){
                return 1;
                break;
            }
        }
    }
    return 0;
}

double mc_average(double p, int num_samples, int L){
    double sum=0.;
    for(int i=0; i<num_samples; i++){
        sum += mc_onestep(p, L);
    }
    sum /= num_samples;
    return sum;
}

void mc_all(int L, int num_samples){
    int ND = 20;
    for(int i=0; i < ND+1; i++){
        double p = (double) i/ND;
        printf("%e, %e\n", p, mc_average(p, num_samples, L));
    }
}

void out(int L, int num_samples){
    // ファイルの用意
    char filename[256];
    sprintf(filename, "out_%02d_2.data", L);
    FILE *file = fopen(filename, "w");
    if(file == NULL){
        perror("Failed to open file. ");
        exit(1);
    }

    // ファイルへの書き込み
    int ND = 1000;
    for(int i=0; i < ND+1; i++){
        double p = (double) i/ND;
        fprintf(file, "%e, %e\n", p, mc_average(p, num_samples, L));
    }

    fclose(file);
}