#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

int main(void){
    char str[] = "c";
    double c = sqrt(4);
    double cs = 1.;
    double ca = c;

    int N = 1000;
    double dtheta = 2.*PI/N;

    // Alfven wave
    double aw[N];
    for(int i=0; i<N; i++){
        double theta = i*dtheta;
        aw[i] = ca * fabs(cos(theta));
    }
    char filename_aw[256];
    sprintf(filename_aw, "out_aw_%s.data", str);
    FILE *file_aw = fopen(filename_aw, "w");
    if(file_aw == NULL){
        perror("Failed to open file. ");
        exit(1);
    }
    for(int i=0; i<N; i++){
        fprintf(file_aw, "%e, %e\n", aw[i]*cos(i*dtheta), aw[i]*sin(i*dtheta));
    }
    fclose(file_aw);

    // fast magnetoacoustic wave
    double fw[N];
    for(int i=0; i<N; i++){
        double theta = i*dtheta;
        fw[i] = sqrt(0.5*((pow(ca, 2)+pow(cs, 2))+sqrt(pow(pow(ca, 2)+pow(cs, 2), 2)-4.*pow(ca, 2)*pow(cs, 2)*pow(cos(theta), 2))));
    }
    char filename_fw[256];
    sprintf(filename_fw, "out_fw_%s.data", str);
    FILE *file_fw = fopen(filename_fw, "w");
    if(file_fw == NULL){
        perror("Failed to open file. ");
        exit(1);
    }
    for(int i=0; i<N; i++){
        fprintf(file_fw, "%e, %e\n", fw[i]*cos(i*dtheta), fw[i]*sin(i*dtheta));
    }
    fclose(file_fw);

    // slow magnetoacoustic wave
    double sw[N];
    for(int i=0; i<N; i++){
        double theta = i*dtheta;
        sw[i] = sqrt(0.5*((pow(ca, 2)+pow(cs, 2))-sqrt(pow(pow(ca, 2)+pow(cs, 2), 2)-4.*pow(ca, 2)*pow(cs, 2)*pow(cos(theta), 2))));
    }
    char filename_sw[256];
    sprintf(filename_sw, "out_sw_%s.data", str);
    FILE *file_sw = fopen(filename_sw, "w");
    if(file_sw == NULL){
        perror("Failed to open file. ");
        exit(1);
    }
    for(int i=0; i<N; i++){
        fprintf(file_sw, "%e, %e\n", sw[i]*cos(i*dtheta), sw[i]*sin(i*dtheta));
    }
    fclose(file_sw);

    return 0;
}