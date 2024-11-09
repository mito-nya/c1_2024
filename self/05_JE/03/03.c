#include <stdio.h>
#include <math.h>

#define pi 3.1415926535

void plot_curve_polar(const char *filename, double theta_offset, double r_offset, double a, double b, int steps) {
    const double theta_min = theta_offset - a * 1.5;
    const double theta_max = theta_offset + a * 1.5;
    const double epsilon = 1e-2; // 許容誤差を小さく設定

    // ファイルを開く
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("ファイルを開けませんでした");
        return;
    }

    // θ の範囲でループ
    for (int i = 0; i <= steps; i++) {
        double theta = theta_min + (theta_max - theta_min) * i / steps;

        // s_theta を計算
        double s_theta = (theta - theta_offset) / a;

        // s_theta^6 を計算
        double s_theta6 = pow(s_theta, 6);

        // s_r6 を計算
        double s_r6 = 1.0 - s_theta6;

        // s_r6 が非負の場合のみ計算を進める
        if (s_r6 >= 0.0) {
            // s_r を計算
            double s_r = pow(s_r6, 1.0 / 6.0);

            // 対応する r を計算（正と負の解がある）
            double r1 = r_offset + b * s_r;
            double r2 = r_offset - b * s_r;

            // r が正の場合のみデカルト座標に変換して出力
            if (r1 > 0) {
                double x1 = r1 * cos(theta);
                double y1 = r1 * sin(theta);
                fprintf(fp, "%.6f %.6f\n", x1, y1);
            }
            if (r2 > 0 && s_r != 0) {
                double x2 = r2 * cos(theta);
                double y2 = r2 * sin(theta);
                fprintf(fp, "%.6f %.6f\n", x2, y2);
            }
        }
    }

    fclose(fp);
}

int main() {
    const int steps = 10000; // 分割数

    // 組み合わせ①
    plot_curve_polar("curve1_1.dat", pi, 4.0, pi * (4 - 0.1) / 5.0, (4 - 0.1) / 5.0, steps);
    plot_curve_polar("curve1_2.dat", 0, 4.0, pi * (1 - 0.1) / 5.0, (1 - 0.1) / 5.0, steps);

    // 組み合わせ②
    plot_curve_polar("curve2_1.dat", pi, 4.0, pi * (3 - 0.1) / 5.0, (3 - 0.1) / 5.0, steps);
    plot_curve_polar("curve2_2.dat", 0, 4.0, pi * (2 - 0.1) / 5.0, (2 - 0.1) / 5.0, steps);

    // 組み合わせ③
    plot_curve_polar("curve3_1.dat", pi, 4.0, pi * (4 - 0.1) / 5.0, (1 - 0.1) / 5.0, steps);
    plot_curve_polar("curve3_2.dat", 0, 4.0, pi * (1 - 0.1) / 5.0, (4 - 0.1) / 5.0, steps);

    // 組み合わせ④
    plot_curve_polar("curve4_1.dat", pi, 4.0, pi * (3 - 0.1) / 5.0, (2 - 0.1) / 5.0, steps);
    plot_curve_polar("curve4_2.dat", 0, 4.0, pi * (2 - 0.1) / 5.0, (3 - 0.1) / 5.0, steps);

    return 0;
}
