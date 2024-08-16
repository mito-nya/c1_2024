#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265
#define gamma 5./3.
#define MIN_ENERGY 1e-10  // エネルギーの最小値
#define MIN_RHO 1e-10     // 密度の最小値
#define MAX_RHO 1e+10     // 密度の最大値

void check_memory_allocation(void *ptr, const char *message) {
    if (ptr == NULL) {
        printf("Memory allocation failed: %s\n", message);
        exit(1);
    }
}

int convert(double *UL, double *UR, double *FL, double *FR, double *flux){
    double rhoL = *(UL+0);
    if (rhoL < MIN_RHO) {
        printf("Warning: rhoL too small, setting to minimum value\n");
        rhoL = MIN_RHO;
    } else if (rhoL > MAX_RHO) {
        printf("Warning: rhoL too large, setting to maximum value\n");
        rhoL = MAX_RHO;
    }
    double uL = *(UL+1)/rhoL;
    double vL = *(UL+2)/rhoL;
    double bxL = *(UL+3);
    double byL = *(UL+4);
    double eL = *(UL+5);
    double VL = uL*uL + vL*vL;
    double BL = bxL*bxL + byL*byL;
    double epsL = (eL - BL/2.)/rhoL - VL/2.;
    double pL = fmax((gamma - 1) * rhoL * epsL, MIN_ENERGY);
    double ptL = pL + BL/2.;
    double csL = sqrt(gamma * pL / rhoL);

    double rhoR = *(UR+0);
    if (rhoR < MIN_RHO) {
        printf("Warning: rhoR too small, setting to minimum value\n");
        rhoR = MIN_RHO;
    } else if (rhoR > MAX_RHO) {
        printf("Warning: rhoR too large, setting to maximum value\n");
        rhoR = MAX_RHO;
    }
    double uR = *(UR+1)/rhoR;
    double vR = *(UR+2)/rhoR;
    double bxR = *(UR+3);
    double byR = *(UR+4);
    double eR = *(UR+5);
    double VR = uR*uR + vR*vR;
    double BR = bxR*bxR + byR*byR;
    double epsR = (eR - BR/2.)/rhoR - VR/2.;
    double pR = fmax((gamma - 1) * rhoR * epsR, MIN_ENERGY);
    double ptR = pR + BR/2.;
    double csR = sqrt(gamma * pR / rhoR);

    *(FL+0) = rhoL * uL;
    *(FL+1) = rhoL * uL * uL + ptL - bxL * bxL;
    *(FL+2) = rhoL * uL * vL - bxL * byL;
    *(FL+3) = 0;
    *(FL+4) = uL * byL - vL * bxL;
    *(FL+5) = (eL + ptL) * uL - bxL * (bxL * uL + byL * vL);

    *(FR+0) = rhoR * uR;
    *(FR+1) = rhoR * uR * uR + ptR - bxR * bxR;
    *(FR+2) = rhoR * uR * vR - bxR * byR;
    *(FR+3) = 0;
    *(FR+4) = uR * byR - vR * bxR;
    *(FR+5) = (eR + ptR) * uR - bxR * (bxR * uR + byR * vR);

    double SL = fmin(0, fmin(uL - csL, uR - csR));
    double SR = fmax(0, fmax(uL + csL, uR + csR));

    for(int i = 0; i < 6; i++){
        *(flux + i) = (SR * *(FL + i) - SL * *(FR + i) + SL * SR * (*(UR + i) - *(UL + i)))/(SR - SL);
    }

    return 0;
}

double f(int i, double x, double y){
    double rho = 25. / (36. * PI);
    double u = -sin(2 * PI * y);
    double v = sin(2 * PI * x);
    double p = 5. / (12. * PI);
    double bx = -sin(2 * PI * y);
    double by = sin(4 * PI * x);
    double e = p / (gamma - 1) + rho * (u*u + v*v) / 2. + (bx*bx + by*by) / 2.;

    if (rho <= 0 || isnan(rho) || isnan(u) || isnan(v) || isnan(p)) {
        printf("Invalid initial condition at x=%e, y=%e: rho=%e, u=%e, v=%e, p=%e\n", x, y, rho, u, v, p);
        exit(1);
    }

    if(i == 0){ // rho
        return rho;
    } else if(i == 1){ // rho*u
        return rho * u;
    } else if(i == 2){ // rho*v
        return rho * v;
    } else if(i == 3){ // bx
        return bx;
    } else if(i == 4){ // by
        return by;
    } else if(i == 5){ // e
        return e;
    } else {
        printf("Invalid index in f(): %d\n", i);
        exit(1);
    }
}

int main(void){
    printf("Starting program\n");

    double ax = 0.0, ay = 0.0;  // 始点
    double bx = 1.0, by = 1.0;  // 終点
    double dx = 1/32.0, dy = 1/32.0; // 空間刻みの幅
    double nu = 0.2;               // CFL数
    double dt = 0.0001 * fmin(dx, dy);  // 時間刻みの幅をさらに小さく
    int Ix = (bx - ax) / dx + 1;   // 空間ステップ数 (x方向)
    int Iy = (by - ay) / dy + 1;   // 空間ステップ数 (y方向)
    int N = 0.50 / dt;             // 時間ステップ数

    printf("Ix = %d, Iy = %d, N = %d\n", Ix, Iy, N);

    double ***U = malloc(Ix * sizeof(double **));
    double ***tmp = malloc(Ix * sizeof(double **));
    check_memory_allocation(U, "U array");
    check_memory_allocation(tmp, "tmp array");

    for(int i = 0; i < Ix; i++) {
        U[i] = malloc(Iy * sizeof(double *));
        tmp[i] = malloc(Iy * sizeof(double *));
        check_memory_allocation(U[i], "U[i] array");
        check_memory_allocation(tmp[i], "tmp[i] array");

        for(int j = 0; j < Iy; j++) {
            U[i][j] = malloc(6 * sizeof(double));
            tmp[i][j] = malloc(6 * sizeof(double));
            check_memory_allocation(U[i][j], "U[i][j] array");
            check_memory_allocation(tmp[i][j], "tmp[i][j] array");
        }
    }

    // 初期条件の設定
    for(int i = 0; i < Ix; i++){
        for(int j = 0; j < Iy; j++){
            for(int index = 0; index < 6; index++){
                U[i][j][index] = f(index, ax + i * dx, ay + j * dy);
                tmp[i][j][index] = U[i][j][index];
            }
        }
    }

    printf("Initial conditions set\n");

    for(int step = 0; step < N; step++){
        if (step % 10 == 0) {
            printf("Step %d of %d\n", step, N);
        }
        double flux[Ix-1][Iy-1][6];
        double F[Ix][Iy][6];
        for(int i = 0; i < Ix-1; i++){
            for(int j = 0; j < Iy-1; j++){
                int im = (int)fmax(0, i-1);
                int ip = (int)fmin(Ix-1, i+1);
                int jm = (int)fmax(0, j-1);
                int jp = (int)fmin(Iy-1, j+1);

                convert(&U[i][j][0], &U[ip][jp][0], &F[i][j][0], &F[ip][jp][0], &flux[i][j][0]);
            }
        }
        for(int i = 1; i < Ix-1; i++){
            for(int j = 1; j < Iy-1; j++){
                for(int k = 0; k < 6; k++){
                    U[i][j][k] = U[i][j][k] - dt/dx*(flux[i][j][k] - flux[i-1][j][k]) - dt/dy*(flux[i][j][k] - flux[i][j-1][k]);
                }

                double rho = U[i][j][0];
                double u = U[i][j][1]/rho;
                double v = U[i][j][2]/rho;
                double bx = U[i][j][3];
                double by = U[i][j][4];
                double B = bx*bx + by*by;
                double V = u*u + v*v;
                double e = U[i][j][5];
                double p = fmax((gamma - 1) * (e - rho * V / 2. - B / 2.), MIN_ENERGY);
                
                if (isnan(rho) || isnan(u) || isnan(v) || isnan(bx) || isnan(by) || isnan(p)) {
                    printf("NaN detected at x=%e, y=%e: rho=%e, u=%e, v=%e, bx=%e, by=%e, p=%e\n", ax + i * dx, ay + j * dy, rho, u, v, bx, by, p);
                    exit(1);  // シミュレーションを停止
                }
            }
        }
    }

    printf("Simulation completed\n");

    // ファイルの用意
    char filename[256];
    sprintf(filename, "orszag_tang_output.data");
    FILE *file = fopen(filename, "w");
    if(file == NULL){
        perror("Failed to open file.");
        exit(1);
    }

    printf("File opened: %s\n", filename);

    // ファイルへの書き込みrho, p, u, v, by
    for(int j = 0; j < Iy; j++){
        for(int i = 0; i < Ix; i++){
            double rho = U[i][j][0];
            double u = U[i][j][1]/rho;
            double v = U[i][j][2]/rho;
            double bx = U[i][j][3];
            double by = U[i][j][4];
            double B = bx*bx + by*by;
            double V = u*u + v*v;
            double e = U[i][j][5];
            double p = fmax((gamma - 1) * (e - rho * V / 2. - B / 2.), MIN_ENERGY);

            fprintf(file, "%e %e %e %e %e %e %e\n", ax + i * dx, ay + j * dy, rho, p, u, v, by);
        }
        fprintf(file, "\n");  // 空行を挿入してyの変化を示す
    }

    fclose(file);
    printf("File closed\n");

    // 動的メモリの解放
    for(int i = 0; i < Ix; i++) {
        for(int j = 0; j < Iy; j++) {
            free(U[i][j]);
            free(tmp[i][j]);
        }
        free(U[i]);
        free(tmp[i]);
    }
    free(U);
    free(tmp);

    printf("Memory freed, program finished successfully.\n");

    return 0;
}
