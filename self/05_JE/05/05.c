#include <stdio.h>
#include <math.h>

#define G 1.0 // 重力定数
#define MU 0.2 // 質量比
#define DT 0.001 // 時間刻み
#define STEPS 100000 // 積分ステップ数

void rk4(double t, double y[], double dt, double mu, double yout[]);
void derivs(double t, double y[], double dydt[], double mu);

int main() {
    double y[4], yout[4];
    double t = 0.0;
    double mu = MU;
    FILE *fp = fopen("orbit.dat", "w");

    // 初期条件
    y[0] = 0.5;  // x座標
    y[1] = 0.0;  // y座標
    y[2] = 0.0;  // x方向速度
    y[3] = 0.5;  // y方向速度

    for (int i = 0; i < STEPS; i++) {
        rk4(t, y, DT, mu, yout);
        t += DT;

        // 解の更新
        for (int j = 0; j < 4; j++) {
            y[j] = yout[j];
        }

        // ファイルへの書き込み
        fprintf(fp, "%lf %lf\n", y[0], y[1]);
    }

    fclose(fp);
    return 0;
}

void rk4(double t, double y[], double dt, double mu, double yout[]) {
    int i;
    double k1[4], k2[4], k3[4], k4[4], ytemp[4];

    derivs(t, y, k1, mu);
    for (i = 0; i < 4; i++) ytemp[i] = y[i] + 0.5 * dt * k1[i];

    derivs(t + 0.5 * dt, ytemp, k2, mu);
    for (i = 0; i < 4; i++) ytemp[i] = y[i] + 0.5 * dt * k2[i];

    derivs(t + 0.5 * dt, ytemp, k3, mu);
    for (i = 0; i < 4; i++) ytemp[i] = y[i] + dt * k3[i];

    derivs(t + dt, ytemp, k4, mu);
    for (i = 0; i < 4; i++) {
        yout[i] = y[i] + (dt / 6.0)*(k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
    }
}

void derivs(double t, double y[], double dydt[], double mu) {
    double x = y[0];
    double y_pos = y[1];
    double vx = y[2];
    double vy = y[3];

    // 主天体の位置
    double x1 = -mu;
    double x2 = 1 - mu;
    double y1 = 0.0;
    double y2 = 0.0;

    // 主天体への距離
    double r1 = sqrt((x - x1)*(x - x1) + (y_pos - y1)*(y_pos - y1));
    double r2 = sqrt((x - x2)*(x - x2) + (y_pos - y2)*(y_pos - y2));

    // 回転座標系での運動方程式
    dydt[0] = vx;
    dydt[1] = vy;
    dydt[2] = 2 * vy + x - ((1 - mu)*(x + mu)) / pow(r1, 3) - (mu*(x - 1 + mu)) / pow(r2, 3);
    dydt[3] = -2 * vx + y_pos - ((1 - mu)*y_pos) / pow(r1, 3) - (mu*y_pos) / pow(r2, 3);
}
