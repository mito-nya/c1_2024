#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

#define gamma 5./3.

double sign(double x){
    if(x > 0) return 1;
    else return -1;
}

int convert(double *UL, double *UR, double *flux){
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

    // 中間状態を埋めていく
    double vaL = fabs(bxL)/sqrt(rhoL);
    double csL = sqrt(gamma*pL/rhoL);
    double caL = sqrt(BL/rhoL);
    double vfL = sqrt((csL*csL+caL*caL+sqrt(pow(csL*csL+caL*caL, 2)-4*csL*csL*vaL*vaL))/2);
    double vsL = sqrt((csL*csL+caL*caL-sqrt(pow(csL*csL+caL*caL, 2)-4*csL*csL*vaL*vaL))/2);

    double vaR = fabs(bxR)/sqrt(rhoR);
    double csR = sqrt(gamma*pR/rhoR);
    double caR = sqrt(BR/rhoR);
    double vfR = sqrt((csR*csR+caR*caR+sqrt(pow(csR*csR+caR*caR, 2)-4*csR*csR*vaR*vaR))/2);
    double vsR = sqrt((csR*csR+caR*caR-sqrt(pow(csR*csR+caR*caR, 2)-4*csR*csR*vaR*vaR))/2);

    double SL = fmin(uL, uR)-fmax(vfL, vfR);
    double SR = fmin(uL, uR)+fmax(vfL, vfR);

    double SM = ((SR-uR)*rhoR*uR-(SL-uL)*rhoL*uL-pR+pL)/((SR-uR)*rhoR-(SL-uL)*rhoL);
    
    // star1個
    double rhoLs = rhoL *(SL-uL)/(SL-SM);
    double rhoRs = rhoR *(SR-uR)/(SR-SM);

    double ps = ((SR-uR)*rhoR*pL-(SL-uL)*rhoL*pR+rhoL*rhoR*(SR-uR)*(SL-uL)*(uR-uL))/((SR-uR)*rhoR-(SL-uL)*rhoL);

    double uLs = SM;
    double uRs = SM;
    double vLs = vL-bxL*byL*(SM-uL)/(rhoL*(SL-uL)*(SL-SM)-bxL*bxL);
    double vRs = vR-bxL*byR*(SM-uR)/(rhoR*(SR-uR)*(SR-SM)-bxR*bxR);
    double wLs = wL-bxL*bzL*(SM-uL)/(rhoL*(SL-uL)*(SL-SM)-bxL*bxL);
    double wRs = wR-bxL*bzR*(SM-uR)/(rhoR*(SR-uR)*(SR-SM)-bxR*bxR);

    double bxLs = bxL;
    double bxRs = bxR;
    double byLs = byL*(rhoL*pow(SL-uL, 2)-bxL*bxL)/(rhoL*(SL-uL)*(SL-SM)-bxL*bxL);
    double byRs = byR*(rhoR*pow(SR-uR, 2)-bxL*bxL)/(rhoR*(SR-uR)*(SR-SM)-bxL*bxL);
    double bzLs = bzL*(rhoL*pow(SL-uL, 2)-bxL*bxL)/(rhoL*(SL-uL)*(SL-SM)-bxL*bxL);
    double bzRs = bzR*(rhoR*pow(SR-uR, 2)-bxL*bxL)/(rhoR*(SR-uR)*(SR-SM)-bxL*bxL);

    double vbL = uL*bxL+vL*byL+wL*bzL;
    double vbR = uR*bxR+vR*byR+wR*bzR;
    double vbLs = uLs*bxLs+vLs*byLs+wLs*bzLs;
    double vbRs = uRs*bxRs+vRs*byRs+wRs*bzRs;

    double eLs = ((SL-uL)*eL-pL*uL+ps*SM+bxL*(vbL-vbLs))/(SL-SM);
    double eRs = ((SR-uR)*eR-pR*uR+ps*SM+bxR*(vbR-vbRs))/(SR-SM);

    double SLs = SM-fabs(bxL)/sqrt(rhoLs);
    double SRs = SM+fabs(bxL)/sqrt(rhoRs);

    // star2個
    double vss = (sqrt(rhoLs)*vLs+sqrt(rhoRs)*vRs+(byRs-byLs)*sign(bxL))/(sqrt(rhoLs)+sqrt(rhoRs));
    double wss = (sqrt(rhoLs)*wLs+sqrt(rhoRs)*wRs+(bzRs-bzLs)*sign(bxL))/(sqrt(rhoLs)+sqrt(rhoRs));

    double byss = (sqrt(rhoLs)*byRs+sqrt(rhoRs)*byLs+sqrt(rhoLs*rhoRs)*(vRs-vLs)*sign(bxL))/(sqrt(rhoLs)+sqrt(rhoRs));
    double bzss = (sqrt(rhoLs)*bzRs+sqrt(rhoRs)*bzLs+sqrt(rhoLs*rhoRs)*(wRs-wLs)*sign(bxL))/(sqrt(rhoLs)+sqrt(rhoRs));

    double vbss = SM*bxL+vss*byss+wss*bzss;

    double eLss = eLs-sqrt(rhoLs)*(vbLs-vbss)*sign(bxL);
    double eRss = eRs-sqrt(rhoRs)*(vbRs-vbss)*sign(bxL);

    // 中間状態を格納
    double utmp[9][6]={{rhoL, rhoLs, rhoLs, rhoRs, rhoRs, rhoR}, 
                    {pL, ps, ps, ps, ps, pR}, 
                    {uL, SM, SM, SM, SM, uR}, 
                    {vL, vLs, vss, vss, vRs, vR}, 
                    {wL, wLs, wss, wss, wRs, wR}, 
                    {bxL, bxL, bxL, bxL, bxL, bxL}, 
                    {byL, byLs, byss, byss, byRs, byR}, 
                    {bzL, bzLs, bzss, bzss, bzRs, bzR}, 
                    {eL, eLs, eLss, eRss, eRs, eR}};

    for(int i=0; i<9; i++){
        for(int j=0; j<6; j++){
            printf("%06f ", utmp[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // x=0がどの中間状態に含まれるか
    int mid = 0;
    if(SL>0){
        mid = 0; 
    }else if(SLs>0){
        mid = 1;
    }else if(SM>0){
        mid = 2;
    }else if(SRs>0){
        mid = 3;
    }else if(SR>0){
        mid = 4;
    }else{
        mid = 5;
    }

    printf("%f %f %f %f %f\n", SL, SLs, SM, SRs, SR);
    printf("%d\n\n", mid);

    // 基本変数から流束ベクトルへ
    double rho = utmp[0][mid];
    double p = utmp[1][mid];
    double u = utmp[2][mid];
    double v = utmp[3][mid];
    double w = utmp[4][mid];
    double bx = utmp[5][mid];
    double by = utmp[6][mid];
    double bz = utmp[7][mid];
    double e = utmp[8][mid];

    *(flux+0) = rho*u;
    *(flux+1) = rho*u*u+p-bx*bx;
    *(flux+2) = rho*u*v-bx*by;
    *(flux+3) = rho*u*w-bx*bz;
    *(flux+4) = 0;
    *(flux+5) = u*by-v*bx;
    *(flux+6) = u*bz-w*bx;
    *(flux+7) = (e+p)*u-bx*(bx*u+by*v+bz*w);

    return 0;
}

double f(int i, double x){
    double rhoL = 1.;
    double pL = 1.;
    double uL = 0;
    double vL = 0;
    double wL = 0;
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
    double a=-0.5;       // 始点
    double b=0.5;        // 終点
    double dx=1/800.;    // 空間刻みの幅
    double nu=0.4;       // CFL数
    double dt=nu*dx/5;   // 時間刻みの幅
    int I=(b-a)/dx+1;    // 空間ステップ数
    int N=0.0001/dt;       // 時間ステップ数

    double U[I][8];      // 数値解を格納する配列
    double tmp[I][8];    // 一時的に格納

    // 初期条件の設定
    for(int i=0; i<I; i++){
        for(int index=0; index<8; index++){
            U[i][index]=f(index, a+i*dx);
            tmp[i][index]=U[i][index];
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

            convert(&U[i][0], &U[ip][0], &flux[i][0]);
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