#include <stdio.h>
#include <math.h>

#define G 1        // 万有引力定数を1に規格化
#define M1 1       // 質量 M1 を1に規格化
#define M2 0.5     // 質量 M2 を0.5に規格化
#define OMEGA 1    // 角速度 ω を1に規格化
#define TOTAL_MASS (M1 + M2)
#define MU (M2 / TOTAL_MASS)             // 質量比 μ = M2 / (M1 + M2)
#define ONE_MINUS_MU (M1 / TOTAL_MASS)   // 1 - μ

double potential(double x, double y) {
    // 質点の位置
    double x1 = -MU;          // 質量 M1 の位置
    double x2 = 1 - MU;       // 質量 M2 の位置

    // 各質点からの距離
    double r1 = sqrt((x - x1) * (x - x1) + y * y);
    double r2 = sqrt((x - x2) * (x - x2) + y * y);

    // 有効ポテンシャルの計算
    return -G * M1 / r1 - G * M2 / r2 - 0.5 * OMEGA * OMEGA * (x * x + y * y);
}

double find_L1() {
    double x = 0.5;  // 初期推定値
    double epsilon = 1e-10;
    int max_iter = 1000;
    int iter = 0;

    while (iter < max_iter) {
        // 質点の位置
        double x1 = -MU;
        double x2 = 1 - MU;

        // 各質点からの距離
        double r1 = x - x1;
        double r2 = x - x2;

        // 力の平衡条件
        double f = G * M1 / (r1 * r1) - G * M2 / (r2 * r2) - OMEGA * OMEGA * x;
        double df = -2 * G * M1 / (r1 * r1 * r1) + 2 * G * M2 / (r2 * r2 * r2) - OMEGA * OMEGA;

        double dx = -f / df;
        x += dx;

        if (fabs(dx) < epsilon) {
            break;
        }
        iter++;
    }
    return x;
}

int main() {
    // L1 点の位置を求める
    double x_L1 = find_L1();
    double phi_L1 = potential(x_L1, 0);

    // グリッドの設定
    int grid_size = 500;
    double x_min = -1.5, x_max = 1.5;
    double y_min = -1.5, y_max = 1.5;
    double dx = (x_max - x_min) / (grid_size - 1);
    double dy = (y_max - y_min) / (grid_size - 1);

    // データをファイルに出力
    FILE *fp = fopen("potential_data.dat", "w");
    for (int j = 0; j < grid_size; j++) {
        double y = y_min + j * dy;
        for (int i = 0; i < grid_size; i++) {
            double x = x_min + i * dx;
            double phi = potential(x, y);
            fprintf(fp, "%f %f %f\n", x, y, phi);
        }
        fprintf(fp, "\n"); // 行の区切り
    }
    fclose(fp);

    // L1 点でのポテンシャル値をファイルに出力
    FILE *fp_phi = fopen("phi_L1.dat", "w");
    fprintf(fp_phi, "%f\n", phi_L1);
    fclose(fp_phi);

    printf("L1 point is at x = %f\n", x_L1);
    printf("Potential at L1 point is phi_L1 = %f\n", phi_L1);

    return 0;
}
