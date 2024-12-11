#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

#define N 5 // 初期のチップ枚数
#define M 6 // 人数
int chip[M];
int dist[N*M];

int dice(){
    return rand()%M;
}

void out(int time){
    // ファイルの用意
    char filename_chip[256];
    sprintf(filename_chip, "./out/out_chip_%06d.data", time);
    FILE *file_chip = fopen(filename_chip, "w");
    if(file_chip == NULL){
        perror("Failed to open file. ");
        exit(1);
    }

    char filename_dist[256];
    sprintf(filename_dist, "./out/out_dist_%06d.data", time);
    FILE *file_dist = fopen(filename_dist, "w");
    if(file_dist == NULL){
        perror("Failed to open file. ");
        exit(1);
    }
    for(int j=0; j<N*M; j++){
        fprintf(file_dist, "%d %e\n", j+1, dist[j]/(double)(M*time));
    }

    for(int j=0; j<M; j++){
        fprintf(file_chip, "%d %d\n", j+1, chip[j]);
    }
    
    fclose(file_dist);
    fclose(file_chip);
    printf("time = %06d\n", time);
}

int main(void){
    for(int i=0; i<M; i++){
        chip[i] = N;
    }

    int time = 0;
    int die = 0;
    int time_max = 100000;

    for(int i=0; i<N*M; i++){
        dist[i]=0;
    }

    for(int i=0; i<time_max; i++){
        die = dice();
        if(chip[die] == 0){
            continue;
        }else{
            chip[die] -= 1;
            die = dice();
            chip[die] += 1;
        }

        for(int j=0; j<M; j++){
            dist[chip[j]]++;
        }

        if(time%10 == 0){    
            out(time);
        }

        time++;
    }

    return 0;
}