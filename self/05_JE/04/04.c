#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define pi 3.1415926535

// s_theta5 関数の定義
double s_theta5(double s_theta) {
    return s_theta * s_theta * s_theta * s_theta * s_theta;
}

void plot_curve_polar(const char *filename, double theta_offset, double r_offset, double a, double b) {
    // θ の範囲を調整
    const double theta_min = theta_offset - a;
    const double theta_max = theta_offset + a;

    const double delta_theta_min = 1e-6; // ステップサイズの最小値
    const double delta_theta_max = 0.01; // ステップサイズの最大値
    const double gradient_threshold = 1e-4; // 勾配の許容値

    // データポイントを保存するための配列
    int max_points = 200000;
    double *x_vals = (double *)malloc(sizeof(double) * max_points);
    double *y_vals = (double *)malloc(sizeof(double) * max_points);
    int count = 0;

    if (x_vals == NULL || y_vals == NULL) {
        perror("メモリの確保に失敗しました");
        return;
    }

    double theta = theta_min;
    while (theta <= theta_max) {
        // s_theta を計算
        double s_theta = (theta - theta_offset) / a;
        double s_theta2 = s_theta * s_theta;
        double s_theta6 = s_theta2 * s_theta2 * s_theta2;

        // s_r6 を計算
        double s_r6 = 1.0 - s_theta6;

        // s_r6 が非負の場合のみ計算を進める
        if (s_r6 >= 0.0) {
            // s_r を計算
            double s_r = pow(s_r6, 1.0 / 6.0);

            // 対応する r1, r2 を計算
            double r1 = r_offset + b * s_r;
            double r2 = r_offset - b * s_r;

            // r1 が正の場合のみデカルト座標に変換して保存
            if (r1 > 0) {
                if (count >= max_points) {
                    max_points *= 2;
                    x_vals = (double *)realloc(x_vals, sizeof(double) * max_points);
                    y_vals = (double *)realloc(y_vals, sizeof(double) * max_points);
                    if (x_vals == NULL || y_vals == NULL) {
                        perror("メモリの再確保に失敗しました");
                        free(x_vals);
                        free(y_vals);
                        return;
                    }
                }
                x_vals[count] = r1 * cos(theta);
                y_vals[count] = r1 * sin(theta);
                count++;
            }

            // r2 が正の場合のみデカルト座標に変換して保存
            if (r2 > 0) {
                if (count >= max_points) {
                    max_points *= 2;
                    x_vals = (double *)realloc(x_vals, sizeof(double) * max_points);
                    y_vals = (double *)realloc(y_vals, sizeof(double) * max_points);
                    if (x_vals == NULL || y_vals == NULL) {
                        perror("メモリの再確保に失敗しました");
                        free(x_vals);
                        free(y_vals);
                        return;
                    }
                }
                x_vals[count] = r2 * cos(theta);
                y_vals[count] = r2 * sin(theta);
                count++;
            }

            // 勾配を計算
            double ds_theta_dtheta = 1.0 / a;
            double s_theta5_val = s_theta5(s_theta);
            double s_r6_power = pow(s_r6, -5.0 / 6.0);
            double dr_ds_theta = b * s_r6_power * (-6.0 * s_theta5_val);
            double dr_dtheta = fabs(dr_ds_theta * ds_theta_dtheta);

            // ステップサイズを勾配に基づいて調整
            double delta_theta = gradient_threshold / (dr_dtheta + 1e-6); // 0除算を防ぐために微小量を加算
            if (delta_theta > delta_theta_max) delta_theta = delta_theta_max;
            if (delta_theta < delta_theta_min) delta_theta = delta_theta_min;

            theta += delta_theta;
        } else {
            // s_r6 が負の場合、大きなステップで次へ進む
            theta += delta_theta_max;
        }
    }

    // 曲線を閉じるために始点を追加
    if (count > 0) {
        x_vals[count] = x_vals[0];
        y_vals[count] = y_vals[0];
        count++;
    }

    // ファイルにデータポイントを出力
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("ファイルを開けませんでした");
        free(x_vals);
        free(y_vals);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%.6f %.6f\n", x_vals[i], y_vals[i]);
    }

    fclose(fp);

    // メモリの解放
    free(x_vals);
    free(y_vals);
}

int main() {
    // 組み合わせ①
    plot_curve_polar("curve1_1.dat", pi, 4.0, pi * (4 - 0.1) / 5.0, (4 - 0.1) / 5.0);
    plot_curve_polar("curve1_2.dat", 0, 4.0, pi * (1 - 0.1) / 5.0, (1 - 0.1) / 5.0);

    // 組み合わせ②
    plot_curve_polar("curve2_1.dat", pi, 4.0, pi * (3 - 0.1) / 5.0, (3 - 0.1) / 5.0);
    plot_curve_polar("curve2_2.dat", 0, 4.0, pi * (2 - 0.1) / 5.0, (2 - 0.1) / 5.0);

    // 組み合わせ③
    plot_curve_polar("curve3_1.dat", pi, 4.0, pi * (4 - 0.1) / 5.0, (1 - 0.1) / 5.0);
    plot_curve_polar("curve3_2.dat", 0, 4.0, pi * (1 - 0.1) / 5.0, (4 - 0.1) / 5.0);

    // 組み合わせ④
    plot_curve_polar("curve4_1.dat", pi, 4.0, pi * (3 - 0.1) / 5.0, (2 - 0.1) / 5.0);
    plot_curve_polar("curve4_2.dat", 0, 4.0, pi * (2 - 0.1) / 5.0, (3 - 0.1) / 5.0);

    return 0;
}
