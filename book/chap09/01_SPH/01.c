#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265
#define gamma 1.4

#define N 100
#define h 0.1
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

typedef struct {
    double x;
    double v;
    double rho;
    double p;
    double epsilon;
    double f;
} Particle;

Particle particles[N];

// 初期条件の設定
void initialize() {
    for (int i = 0; i < N; i++) {
        particles[i].x = (double)i / N;
        particles[i].v = 0.;
        if (particles[i].x < 0.5) {
            particles[i].rho = 1.;
            particles[i].p = 1.;
            particles[i].epsilon = 2.5;
        } else {
            particles[i].rho = 0.125;
            particles[i].p = 0.1;
            particles[i].epsilon = 2.0;
        }
    }
}

// 密度の計算
void computeDensity() {
    for (int i = 0; i < N; i++) {
        particles[i].rho = 0.0;
        for (int j = 0; j < N; j++) {
            particles[i].rho += mass * W(particles[i].x - particles[j].x);
        }
    }
}

// 圧力の計算
void computePressure() {
    for (int i = 0; i < N; i++) {
        particles[i].p = (gamma - 1) * particles[i].rho * particles[i].epsilon;
    }
}

// 力の計算
void computeForce() {
    for (int i = 0; i < N; i++) {
        particles[i].f = 0.0;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                double rij = particles[i].x - particles[j].x;
                double Wij = dW(rij);
                particles[i].f -= mass * (particles[i].p / pow(particles[i].rho, 2) + particles[j].p / pow(particles[j].rho, 2)) * Wij;
            }
        }
    }
}

// 内部エネルギーの更新
void updateEnergy() {
    for (int i = 0; i < N; i++) {
        double depsilon_dt = 0.0;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                double rij = particles[i].x - particles[j].x;
                double Wij = dW(rij);
                double vij = particles[i].v - particles[j].v;
                depsilon_dt += mass * (particles[j].p / pow(particles[j].rho, 2)) * vij * Wij;
            }
        }
        particles[i].epsilon += depsilon_dt * dt;
    }
}

// 時間発展
void update() {
    // 半ステップの速度を更新
    for (int i = 0; i < N; i++) {
        particles[i].v += 0.5 * particles[i].f * dt;
    }
    // 位置を更新
    for (int i = 0; i < N; i++) {
        particles[i].x += particles[i].v * dt;
    }
    // 力を再計算
    computeDensity();
    computePressure();
    computeForce();
    updateEnergy();
    // 残りの半ステップの速度を更新
    for (int i = 0; i < N; i++) {
        particles[i].v += 0.5 * particles[i].f * dt;
    }
}

int main(void) {
    int step = (int)(time / dt);

    initialize();
    for (int i = 0; i < step; i++) {
        update();
        printf("# x: %f, v: %f, rho: %f, p: %f, epsilon: %f\n", particles[50].x, particles[50].v, particles[50].rho, particles[50].p, particles[50].epsilon);
    }

    for (int i = 0; i < N; i++) {
        printf("%f, %f\n", particles[i].x, particles[i].rho);
    }

    return 0;
}
