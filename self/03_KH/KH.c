#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 定数の定義
#define NUM_PARTICLES 1000
#define MASS 1.0
#define H 0.1
#define DT 0.01
#define NUM_STEPS 1000
#define GAMMA 1.4
#define RHO0 1.0
#define K 1.0
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 粒子の状態を表す構造体
typedef struct {
    double x, y;
    double vx, vy;
    double density;
    double pressure;
    double fx, fy;
    int layer;  // 層情報を追加（0: 下層、1: 上層）
} Particle;

// カーネル関数の定義
double kernel(double r, double h) {
    double q = r / h;
    if (q <= 1.0) {
        return (1.0 - 1.5 * q * q + 0.75 * q * q * q) / (M_PI * h * h * h);
    } else if (q <= 2.0) {
        return 0.25 * pow(2.0 - q, 3) / (M_PI * h * h * h);
    } else {
        return 0.0;
    }
}

// 距離の計算
double distance(Particle p1, Particle p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// 密度の計算
void compute_densities(Particle particles[]) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].density = 0.0;
        for (int j = 0; j < NUM_PARTICLES; j++) {
            double r = distance(particles[i], particles[j]);
            particles[i].density += MASS * kernel(r, H);
        }
    }
}

// 圧力の計算
void compute_pressures(Particle particles[]) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].pressure = K * (particles[i].density - RHO0);
    }
}

// 力の計算
void compute_forces(Particle particles[]) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].fx = 0.0;
        particles[i].fy = 0.0;
        for (int j = 0; j < NUM_PARTICLES; j++) {
            if (i != j) {
                double r = distance(particles[i], particles[j]);
                if (r > 0) {
                    double force_mag = -MASS * (particles[i].pressure / (particles[i].density * particles[i].density)
                        + particles[j].pressure / (particles[j].density * particles[j].density)) * kernel(r, H);
                    particles[i].fx += force_mag * (particles[i].x - particles[j].x) / r;
                    particles[i].fy += force_mag * (particles[i].y - particles[j].y) / r;
                }
            }
        }
    }
}

// 粒子の初期化
void initialize_particles(Particle particles[]) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].x = 2.0 * ((double)rand() / RAND_MAX);  // 0から2の範囲で配置
        particles[i].y = 2.0 * ((double)rand() / RAND_MAX);  // 0から2の範囲で配置
        if (particles[i].y > 1.0) {
            particles[i].vx = 0.5;  // 上部の流れ
            particles[i].layer = 1;  // 上層
        } else {
            particles[i].vx = -0.5;  // 下部の流れ
            particles[i].layer = 0;  // 下層
        }
        particles[i].vy = 0.1 * ((double)rand() / RAND_MAX - 0.5);  // 摂動を強化
        particles[i].density = 0.0;
        particles[i].pressure = 0.0;
        particles[i].fx = 0.0;
        particles[i].fy = 0.0;
    }
}

// データの保存
void save_data(Particle particles[], int step) {
    char filename[256];
    sprintf(filename, "output_step_%03d.dat", step);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("ファイルのオープンに失敗しました");
        exit(1);
    }
    for (int i = 0; i < NUM_PARTICLES; i++) {
        fprintf(file, "%f %f %d\n", particles[i].x, particles[i].y, particles[i].layer);
    }
    fclose(file);
}

// シミュレーションの実行
void run_simulation(Particle particles[]) {
    for (int step = 0; step < NUM_STEPS; step++) {
        compute_densities(particles);
        compute_pressures(particles);
        compute_forces(particles);

        // 粒子位置と速度の更新
        for (int i = 0; i < NUM_PARTICLES; i++) {
            particles[i].vx += particles[i].fx * DT / particles[i].density;
            particles[i].vy += particles[i].fy * DT / particles[i].density;
            particles[i].x += particles[i].vx * DT;
            particles[i].y += particles[i].vy * DT;

            // 位置の境界条件を適用（x方向の周期境界条件のみ）
            if (particles[i].x < 0) particles[i].x += 2.0;
            if (particles[i].x > 2.0) particles[i].x -= 2.0;
        }

        // データの保存
        save_data(particles, step);

        // 簡易的な可視化用出力（ステップごとに位置を表示）
        if (step % 10 == 0) {
            printf("Step: %d\n", step);
            for (int i = 0; i < NUM_PARTICLES; i++) {
                printf("Particle %d: (%f, %f)\n", i, particles[i].x, particles[i].y);
            }
        }
    }
}

int main() {
    Particle particles[NUM_PARTICLES];
    initialize_particles(particles);
    run_simulation(particles);
    return 0;
}
