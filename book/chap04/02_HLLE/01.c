#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

#define gamma 5./3.

int convert(double *UL, double *UR, double *FL, double *FR, double *flux){
    // 保存量ベクトルから基本変数へ
    double rhoL = *(UL+0);
    double uL = *(UL+1)/rhoL;
    double vL = *(UL+2)/rhoL;
    double wL = *(UL+3)/rhoL;
    double bxL = *(UL+4);
    double byL = *(UL+5);
    double bzL = *(UL+6);
    double eL = *(UL+7);
    double VL = uL*uL+vL*vL+wL*wL;
    double BL = bxL*bxL+byL*byL+bzL*bzL;
    double epsL = (eL-BL/2.)/rhoL-vL/2.;
    double pL = (gamma-1)*rhoL*epsL;
    double ptL = pL+BL/2.;
    double csL = sqrt(gamma*pL/rhoL);

    double rhoR = *(UR+0);
    double uR = *(UR+1)/rhoR;
    double vR = *(UR+2)/rhoR;
    double wR = *(UR+3)/rhoR;
    double bxR = *(UR+4);
    double byR = *(UR+5);
    double bzR = *(UR+6);
    double eR = *(UR+7);
    double VR = uR*uR+vR*vR+wR*wR;
    double BR = bxR*bxR+byR*byR+bzR*bzR;
    double epsR = (eR-BR/2.)/rhoR-VR/2.;
    double pR = (gamma-1)*rhoR*epsR;
    double ptR = pR+BR/2.;
    double csR = sqrt(gamma*pR/rhoR);

    // 基本変数から流束ベクトルへ
    *(FL+0) = rhoL*uL;
    *(FL+1) = rhoL*uL*uL+ptL-bzL*bzL;
    *(FL+2) = rhoL*uL*vL-bxL*byL;
    *(FL+3) = rhoL*uL*wL-bxL*bzL;
    *(FL+4) = 0;
    *(FL+5) = uL*byL-vL*bxL;
    *(FL+6) = uL*bzL-wL*bxL;
    *(FL+7) = (eL+ptL)*uL-bxL*(bxL*uL+byL*vL+bzL*wL);

    *(FR+0) = rhoR*uR;
    *(FR+1) = rhoR*uR*uR+ptR-bzR*bzR;
    *(FR+2) = rhoR*uR*vR-bxR*byR;
    *(FR+3) = rhoR*uR*wR-bxR*bzR;
    *(FR+4) = 0;
    *(FR+5) = uR*byR-vR*bxR;
    *(FR+6) = uR*bzR-wR*bxR;
    *(FR+7) = (eR+ptR)*uR-bxR*(bxR*uR+byR*vR+bzR*wR);

    // HLLE
    double ubb = sqrt(uL*uR);
    double csbb = sqrt(csL*csR);
    double SL = fmin(0, ubb-csbb);
    double SR = fmax(0, ubb+csbb);

    for(int i=0; i<8; i++){
        *(flux+i) = (SR * *(FL+i) - SL * *(FR+i) + SL*SR*(*(UR+i)-*(UL+i)))/(SR-SL);
    }

    return 0;
}

double f(int i, double x){
    double rhoL = 1.;
    double pL = 1.;
    double uL = 0;
    double vL = 0;
    double wL = 0.9;
    double bxL = 0.75;
    double byL = 1;
    double bzL = 0;

    double rhoR = 0.125;
    double pR = 0.1;
    double uR = 0;
    double vR = 0;
    double wR = 0;
    double bxR = 0.75;
    double byR = -1;
    double bzR = 0;

    double VL = uL*uL+vL*vL+wL*wL;
    double BL = bxL*bxL+byL*byL+bzL*bzL;
    double VR = uR*uR+vR*vR+wR*wR;
    double BR = bxR*bxR+byR*byR+bzR*bzR;

    if(i==0){ // rho
        if(x<0) return rhoL;
        else return rhoR;
    }else if(i==1){ // rho*u
        if(x<0) return uL*f(0, x);
        else return uR*f(0, x);
    }else if(i==2){ // rho*v
        if(x<0) return vL*f(0, x);
        else return vR*f(0, x);
    }else if(i==3){ // rho*w
        if(x<0) return wL*f(0, x);
        else return wR*f(0, x);
    }else if(i==4){
        if(x<0) return bxL;
        else return bxR;
    }else if(i==5){
        if(x<0) return byL;
        else return byR;
    }else if(i==6){
        if(x<0) return bzL;
        else return bzR;
    }else if(i==7){
        if(x<0) return pL/(gamma-1)+rhoL*VL/2.+BL/2.;
        else return pR/(gamma-1)+rhoR*VR/2.+BR/2.;
    }else{
        exit(1);
    }
}

int main(void){
    double a = -0.5;       // 始点
    double b = 0.5;        // 終点
    double dx = 1/800.;    // 空間刻みの幅
    double nu = 0.2;       // CFL数
    double dt = nu*dx/5;   // 時間刻みの幅
    int I = (b-a)/dx+1;    // 空間ステップ数
    int N = 0.10/dt;       // 時間ステップ数

    double U[I][8];      // 数値解を格納する配列
    double tmp[I][8];    // 一時的に格納

    // 初期条件の設定
    for(int i=0; i<I; i++){
        for(int index=0; index<8; index++){
            U[i][index] = f(index, a+i*dx);
            tmp[i][index] = U[i][index];
        }
    }

    for(int step=0; step<N; step++){
        double flux[I-1][8];
        double F[I][8];
        for(int i=0; i<I-1; i++){
            // 固定境界条件を課す
            int im = (int)fmax(0, i-1);
            int ip = (int)fmin(I-1, i+1);
            int ipp = (int)fmin(I-1, i+2);

            convert(&U[i][0], &U[ip][0], &F[i][0], &F[i+1][0], &flux[i][0]);
        }
        for(int i=1; i<I-1; i++){
            for(int j=0; j<8; j++){
                U[i][j] = U[i][j] - dt/dx*(flux[i][j]-flux[i-1][j]);
            }
        }
    }

    // ファイルの用意
    char filename[256];
    sprintf(filename, "out.data");
    FILE *file = fopen(filename, "w");
    if(file == NULL){
        perror("Failed to open file. ");
        exit(1);
    }

    // ファイルへの書き込み rho, p, u, v, by
    for(int i=0; i<I; i++){
        double rho=U[i][0];
        double u=U[i][1]/rho;
        double v=U[i][2]/rho;
        double w=U[i][3]/rho;
        double bx=U[i][4];
        double by=U[i][5];
        double bz=U[i][6];
        double B = bx*bx+by*by+bz*bz;
        double V = u*u+v*v+w*w;
        double e = U[i][7];
        double p = (gamma-1)*(e-rho*V/2.-B/2.);
        
        fprintf(file, "%e, %e, %e, %e, %e, %e\n", a+i*dx, rho, p, u, v, by);
    }

    fclose(file);
    return 0;
}