#include <stdio.h>
#include <math.h>

#define pi 3.1415926535

int main() {
    // 曲線1のパラメータ
    const double a1 = pi * 3.9 / 5.0;
    const double b1 = 3.9 / 5.0;

    // 曲線2のパラメータ
    const double a2 = pi * 0.9 / 5.0;
    const double b2 = 0.9 / 5.0;

    // xとyの範囲とステップ
    const double x_min = -6.0;
    const double x_max = 6.0;
    const double y_min = -6.0;
    const double y_max = 6.0;
    const int steps = 4000;
    const double epsilon = 1e-2;

    // 曲線1の点を保存するファイルを開く
    FILE *fp1 = fopen("curve1_points.dat", "w");
    if (fp1 == NULL) {
        perror("curve1_points.dat を開けませんでした");
        return 1;
    }

    // 曲線2の点を保存するファイルを開く
    FILE *fp2 = fopen("curve2_points.dat", "w");
    if (fp2 == NULL) {
        perror("curve2_points.dat を開けませんでした");
        fclose(fp1);
        return 1;
    }

    // xとyの範囲でループ
    for (int i = 0; i <= steps; i++) {
        double x = x_min + (x_max - x_min) * i / steps;
        for (int j = 0; j <= steps; j++) {
            double y = y_min + (y_max - y_min) * j / steps;
            double r = sqrt(x * x + y * y);
            double theta = atan2(y, x);

            // 曲線1のための角度調整
            double theta1 = theta;
            if (theta1 < 0) {
                theta1 += 2 * pi;
            }

            // 曲線1の評価
            double s_theta1 = (theta1 - pi) / a1;
            double s_r1 = (r - 4) / b1;
            double s_theta1_6 = s_theta1 * s_theta1 * s_theta1 * s_theta1 * s_theta1 * s_theta1;
            double s_r1_6 = s_r1 * s_r1 * s_r1 * s_r1 * s_r1 * s_r1;
            double lhs1 = s_theta1_6 + s_r1_6;

            if (fabs(lhs1 - 1.0) < epsilon) {
                fprintf(fp1, "%.6f %.6f\n", x, y);
            }

            // 曲線2の評価（角度調整なし）
            double s_theta2 = theta / a2;
            double s_r2 = (r - 4) / b2;
            double s_theta2_6 = s_theta2 * s_theta2 * s_theta2 * s_theta2 * s_theta2 * s_theta2;
            double s_r2_6 = s_r2 * s_r2 * s_r2 * s_r2 * s_r2 * s_r2;
            double lhs2 = s_theta2_6 + s_r2_6;

            if (fabs(lhs2 - 1.0) < epsilon) {
                fprintf(fp2, "%.6f %.6f\n", x, y);
            }
        }
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
