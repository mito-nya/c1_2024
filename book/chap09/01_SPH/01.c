#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265
#define gamma 1.4

#define N 100
#define h 0.1
#define M 0.01
#define dt 0.0001
#define time 0.2
#define D 1

double mass = 1.0 / N;

// カーネル関数の定義
double W(double u) {
    double sigma;
    if (D == 1) {
        sigma = 1. / 6;
    } else if (D == 2) {
        sigma = 5. / (14. * PI);
    } else {
        sigma = 1. / (4. * PI);
    }

    double q = fabs(u) / h;
    if (q < 1) {
        return sigma / pow(h, D) * (pow(2 - q, 3) - 4 * pow(1 - q, 3));
    } else if (q < 2) {
        return sigma / pow(h, D) * (pow(2 - q, 3));
    } else {
        return 0;
    }
}

// カーネル関数の微分
double dW(double u) {
    double sigma;
    if (D == 1) {
        sigma = 1. / 6;
    } else if (D == 2) {
        sigma = 5. / (14. * PI);
    } else {
        sigma = 1. / (4. * PI);
    }

    double q = fabs(u) / h;
    if (q < 1) {
        return sigma / pow(h, D) * (-3 * pow(2 - q, 2) + 12 * pow(1 - q, 2)) * ((u > 0) ? 1 : -1);
    } else if (q < 2) {
        return sigma / pow(h, D) * (-3 * pow(2 - q, 2)) * ((u > 0) ? 1 : -1);
    } else {
        return 0;
    }
}

// カーネル関数のラプラシアン
double ddW(double u) {
    double sigma;
    if (D == 1) {
        sigma = 1. / 6;
    } else if (D == 2) {
        sigma = 5. / (14. * PI);
    } else {
        sigma = 1. / (4. * PI);
    }

    double q = fabs(u) / h;
    if (q < 1) {
        return sigma / pow(h, D) * (6 * pow(2 - q, 1) - 12 * pow(1 - q, 1)) * ((u > 0) ? 1 : -1);
    } else if (q < 2) {
        return sigma / pow(h, D) * (6 * pow(2 - q, 1)) * ((u > 0) ? 1 : -1);
    } else {
        return 0;
    }
}

typedef struct {
    double position;
    double velocity;
    double density;
    double pressure;
    double force;
} Particle;

Particle particles[N];

// 初期条件の設定
void initialize() {
    for (int i = 0; i < N; i++) {
        int subN = (int)(N*8./9.);
        if(i < subN){
            particles[i].position = (double)(0.5*i/subN);
            particles[i].velocity = 0.;
            particles[i].density = 1.;
            particles[i].pressure = 0.;
            particles[i].force = 0;
        } else {
            particles[i].position = 0.5 + 0.5*(i-subN+0.)/(N-subN+0.);
            particles[i].velocity = 0.;
            particles[i].density = 0.125;
            particles[i].pressure = 0.0;
            particles[i].force = 0.0;
        }
    }
}

// 密度の計算
void computeDensity() {
    for(int i=0; i<N; i++){
        double sum = 0;
        for(int j=0; j<N; j++){
            if(i==j){
                continue;
            }else{
                double diff = fabs(particles[i].position-particles[j].position);
                sum += W(diff);
            }
        }
        particles[i].position = sum;
    }
}

// 圧力の計算
void computePressure() {
    double pressureStiffness = 1.;
    double restDensity = 1.;
    for (int i = 0; i < N; i++) {
        particles[i].pressure = pressureStiffness * (particles[i].density - restDensity);
    }
}

// 力の計算
void computeForce(){
    for(int i=0; i<N; i++){
        // 圧力項
        double pressureTerm = 0;
        for(int j=0; j<N; j++){
            if(i==j){
                continue;
            }else{
                double diff = fabs(particles[i].position-particles[j].position);
                pressureTerm -= M*(particles[j].pressure - particles[i].pressure)/(2*particles[i].density * particles[j].density) * dW(diff);
            }
        }
        // 粘性項
        double nu = 0.1;
        double viscosityTerm = 0;
        for(int j=0; j<N; j++){
            if(i==j){
                continue;
            }else{
                double diff = fabs(particles[i].position-particles[j].position);
                viscosityTerm += nu * M * (particles[j].velocity - particles[i].velocity)/particles[j].density * ddW(diff);
            }
        }
        // 境界
        double ks = 1.;
        double kd = 1.;
        double fcol = (ks*particles[i].position+kd*particles[i].velocity)-(ks*(1-particles[i].position)-kd*particles[i].velocity);


        particles[i].force = pressureTerm + viscosityTerm+fcol;
    }
}

// 時間発展
void update() {
    double prev_a[N];
    for(int i=0; i<N; i++){
        prev_a[i] = particles[i].force / M;
    }

    computeDensity();
    computePressure();
    computeForce();

    for(int i=0; i<N; i++){
        particles[i].position += particles[i].velocity * dt + 0.5 * particles[i].force / M * dt * dt;
        particles[i].velocity += 0.5 * (prev_a[i] + particles[i].force / M) * dt;
    }
}

void out(int step){
    // ファイルの用意
    char filename[256];
    sprintf(filename, "out_%04d.data", step);
    FILE *file = fopen(filename, "w");
    if(file == NULL){
        perror("Failed to open file. ");
        exit(1);
    }
    // ファイルへの書き込み
    for(int i=0; i<N; i++){
        double x = particles[i].position;
        double rho = particles[i].density;
        double v = particles[i].velocity;
        double p = particles[i].pressure;
        double f = particles[i].force;
        fprintf(file, "%e, %e, %e, %e, %e\n", x, rho, v, p, f);
    }
    fclose(file);    
}

int main(void) {
    int step_max = (int)(time / dt);

    initialize();
    for(int step=0; step<step_max; step++){
        update();
        out(step);
    }

    return 0;
}
