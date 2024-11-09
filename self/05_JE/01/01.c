#include <stdio.h>
#include <math.h>

#define pi 3.1415926535

void plot_curve(const char *filename, double theta_offset, double theta_scale, double r_scale, int points) {
    double theta_min = theta_offset - theta_scale;
    double theta_max = theta_offset + theta_scale;

    // ファイルを開く
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("ファイルを開くことができませんでした");
        return;
    }

    for (int i = 0; i <= points; i++) {
        double theta = theta_min + (theta_max - theta_min) * i / points;
        double s = (theta - theta_offset) / theta_scale;
        if (fabs(s) <= 1) {
            double one_minus_s6 = 1 - pow(s, 6);
            if (one_minus_s6 >= 0) {
                double r = 1 + r_scale * pow(one_minus_s6, 1.0 / 6.0);
                double x = r * cos(theta);
                double y = r * sin(theta);
                fprintf(fp, "%.6f %.6f\n", x, y);
            }
        }
    }

    fclose(fp);
}

int main() {
    const int points = 1000; // 描画するポイント数

    // 曲線1のパラメータ
    double a1 = pi * 3.9 / 5.0;
    double b1 = 3.9 / 5.0;
    plot_curve("curve1.dat", pi, a1, b1, points);

    // 曲線2のパラメータ
    double a2 = pi * 0.9 / 5.0;
    double b2 = 0.9 / 5.0;
    plot_curve("curve2.dat", 0.0, a2, b2, points);

    return 0;
}
