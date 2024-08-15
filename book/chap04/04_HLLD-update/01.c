// 1次元HLLD近似リーマン解法
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265
#define gamma 1.4

double sgn(double x){
    if(x==0){
        return 0;
    }else if(x>0){
        return 1;
    }else{
        return -1;
    }
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

void convert(double *uL, double *uR, double *U){
    // indexを引っ張ってくる用
    int L = 0;
    int Ls = 1;
    int Lss = 2;
    int Rss = 3;
    int Rs = 4;
    int R = 5;

    int rho = 0;
    int pT = 1;
    int u = 2;
    int v = 3;
    int w = 4;
    int Bx = 5;
    int By = 6;
    int Bz = 7;
    int e = 8;

    double vrho = *(uL+0);
    double vu = *(uL+1)/vrho;
    double vv = *(uL+2)/vrho;
    double vw = *(uL+3)/vrho;
    double vBx = *(uL+4);
    double vBy = *(uL+5);
    double vBz = *(uL+6);
    double ve = *(uL+7);

    double vp = (gamma-1)* (ve-0.5*vrho*(vu*vu+vv*vv+vw*vw)-0.5*(vBx*vBx+vBy*vBy+vBz*vBz));
    double vpT = vp + 0.5*(vBx*vBx+vBy*vBy+vBz*vBz);
    
    *(U+rho*6+L) = vrho;
    *(U+pT*6+L) = vpT;
    *(U+u*6+L) = vu;
    *(U+v*6+L) = vv;
    *(U+w*6+L) = vw;
    *(U+Bx*6+L) = vBx;
    *(U+By*6+L) = vBy;
    *(U+Bz*6+L) = vBz;
    *(U+e*6+L) = ve;

    // 右側についても同様に

    vrho = *(uR+0);
    vu = *(uR+1)/vrho;
    vv = *(uR+2)/vrho;
    vw = *(uR+3)/vrho;
    vBx = *(uR+4);
    vBy = *(uR+5);
    vBz = *(uR+6);
    ve = *(uR+7);

    vp = (gamma-1)* (ve-0.5*vrho*(vu*vu+vv*vv+vw*vw)-0.5*(vBx*vBx+vBy*vBy+vBz*vBz));
    vpT = vp + 0.5*(vBx*vBx+vBy*vBy+vBz*vBz);
    
    *(U+rho*6+R) = vrho;
    *(U+pT*6+R) = vpT;
    *(U+u*6+R) = vu;
    *(U+v*6+R) = vv;
    *(U+w*6+R) = vw;
    *(U+Bx*6+R) = vBx;
    *(U+By*6+R) = vBy;
    *(U+Bz*6+R) = vBz;
    *(U+e*6+R) = ve;
}

void compute_flux(double *U, double *F){
    // indexを引っ張ってくる用
    int L = 0;
    int Ls = 1;
    int Lss = 2;
    int Rss = 3;
    int Rs = 4;
    int R = 5;

    int rho = 0;
    int pT = 1;
    int u = 2;
    int v = 3;
    int w = 4;
    int Bx = 5;
    int By = 6;
    int Bz = 7;
    int e = 8;

    // 色々速度を求めておく
    double BL = pow(*(U+Bx*6+L), 2)+pow(*(U+By*6+L), 2)+pow(*(U+Bz*6+L), 2);
    double vL = pow(*(U+u*6+L), 2)+pow(*(U+v*6+L), 2)+pow(*(U+w*6+L), 2);
    double aL = sqrt(gamma**(U+pT*6+L)/ *(U+rho*6+L));
    double caL = BL/sqrt(*(U+rho*6+L));
    double caxL = *(U+Bx*6+L)/sqrt(*(U+rho*6+L));
    double cfxL = sqrt(fmax(1e-12, (aL*aL+caL*caL+sqrt(pow(aL*aL+caL*caL, 2)-4*aL*aL*caxL*caxL))/2));
    double csxL = sqrt(fmax(1e-12, (aL*aL+caL*caL-sqrt(pow(aL*aL+caL*caL, 2)-4*aL*aL*caxL*caxL))/2));

    double BR = pow(*(U+Bx*6+R), 2)+pow(*(U+By*6+R), 2)+pow(*(U+Bz*6+R), 2);
    double vR = pow(*(U+u*6+R), 2)+pow(*(U+v*6+R), 2)+pow(*(U+w*6+R), 2);
    double aR = sqrt(gamma**(U+pT*6+R)/ *(U+rho*6+R));
    double caR = BR/sqrt(*(U+rho*6+R));
    double caxR = *(U+Bx*6+R)/sqrt(*(U+rho*6+R));
    double cfxR = sqrt((aR*aR+caR*caR+sqrt(pow(aR*aR+caR*caR, 2)-4*aR*aR*caxR*caxR))/2);
    double csxR = sqrt((aR*aR+caR*caR-sqrt(pow(aR*aR+caR*caR, 2)-4*aR*aR*caxR*caxR))/2);

    double SL = fmin(*(U+u*6+L)-cfxL, *(U+u*6+R)-cfxR);
    double SR = fmin(*(U+u*6+L)+cfxL, *(U+u*6+R)+cfxR);

    double epsilon = 1e-12;

    if (fabs(SL) < epsilon) SL = epsilon * sgn(SL);
    if (fabs(SR) < epsilon) SR = epsilon * sgn(SR);

    *(U+Bx*6+Ls) = *(U+Bx*6+L);
    *(U+Bx*6+Lss) = *(U+Bx*6+L);
    *(U+Bx*6+Rss) = *(U+Bx*6+L);
    *(U+Bx*6+Rs) = *(U+Bx*6+L);

    double denominator = (SR - *(U+u*6+R)) * *(U+rho*6+R) - (SL - *(U+u*6+L)) * *(U+rho*6+L);

    // 分母が非常に小さい場合、epsilonを加える
    if (fabs(denominator) < epsilon) {
        denominator = epsilon * sgn(denominator);
    }

    // double SM = ( (SR - *(U+u*6+R)) * *(U+rho*6+R) * *(U+u*6+R) - 
    //               (SL - *(U+u*6+L)) * *(U+rho*6+L) * *(U+u*6+L) - 
    //            *(U+pT*6+R) + *(U+pT*6+L)) / denominator;
    double SM = 0.5*(SL+SR);
    
    //double SM = ( (SR-*(U+u*6+R)) * *(U+rho*6+R) * *(U+u*6+R) - (SL-*(U+u*6+L)) * *(U+rho*6+L) * *(U+u*6+L) - *(U+pT*6+R) + *(U+pT*6+L))/( (SR-*(U+u*6+R)) * *(U+rho*6+R) - (SL-*(U+u*6+L)) * *(U+rho*6+L));

    *(U+u*6+Ls) = SM;
    *(U+u*6+Lss) = SM;
    *(U+u*6+Rss) = SM;
    *(U+u*6+Rs) = SM;

    double pTs = *(U+pT*6+L) + *(U+rho*6+L) * (SL- *(U+u*6+L))*(SM- *(U+u*6+L));
    *(U+pT*6+Ls) = pTs;
    *(U+pT*6+Lss) = pTs;
    *(U+pT*6+Rss) = pTs;
    *(U+pT*6+Rs) = pTs;

    *(U+rho*6+Ls) = *(U+rho*6+L) * (SL - *(U+u*6+L)) / (SL-SM);
    *(U+rho*6+Rs) = *(U+rho*6+R) * (SR - *(U+u*6+R)) / (SR-SM);

    *(U+v*6+Ls) = *(U+v*6+L) - *(U+Bx*6+L) * *(U+By*6+L) * (SM-*(U+u*6+L))/(*(U+rho*6+L) *(SL-*(U+u*6+L)*(SL-SM)-pow(*(U+Bx*6+L), 2)));
    *(U+v*6+Rs) = *(U+v*6+R) - *(U+Bx*6+R) * *(U+By*6+R) * (SM-*(U+u*6+R))/(*(U+rho*6+R) *(SR-*(U+u*6+R)*(SR-SM)-pow(*(U+Bx*6+R), 2)));

    *(U+By*6+Ls) = *(U+By*6+L)*(*(U+rho*6+L)*pow(SL-*(U+u*6+L), 2)-pow(*(U+Bx*6+L), 2))/(*(U+rho*6+L) *(SL-*(U+u*6+L)*(SL-SM)-pow(*(U+Bx*6+L), 2)));
    *(U+By*6+Rs) = *(U+By*6+R)*(*(U+rho*6+R)*pow(SR-*(U+u*6+R), 2)-pow(*(U+Bx*6+R), 2))/(*(U+rho*6+R) *(SR-*(U+u*6+R)*(SR-SM)-pow(*(U+Bx*6+R), 2)));

    *(U+w*6+Ls) = *(U+w*6+L) - *(U+Bx*6+L) * *(U+Bz*6+L) * (SM-*(U+u*6+L))/(*(U+rho*6+L) *(SL-*(U+u*6+L)*(SL-SM)-pow(*(U+Bx*6+L), 2)));
    *(U+w*6+Rs) = *(U+w*6+R) - *(U+Bx*6+R) * *(U+Bz*6+R) * (SM-*(U+u*6+R))/(*(U+rho*6+R) *(SR-*(U+u*6+R)*(SR-SM)-pow(*(U+Bx*6+R), 2)));

    *(U+Bz*6+Ls) = *(U+Bz*6+L)*(*(U+rho*6+L)*pow(SL-*(U+u*6+L), 2)-pow(*(U+Bx*6+L), 2))/(*(U+rho*6+L) *(SL-*(U+u*6+L)*(SL-SM)-pow(*(U+Bx*6+L), 2)));
    *(U+Bz*6+Rs) = *(U+Bz*6+R)*(*(U+rho*6+R)*pow(SR-*(U+u*6+R), 2)-pow(*(U+Bx*6+R), 2))/(*(U+rho*6+R) *(SR-*(U+u*6+R)*(SR-SM)-pow(*(U+Bx*6+R), 2)));

    double vBL = *(U+u*6+L) * *(U+Bx*6+L) + *(U+v*6+L) * *(U+By*6+L) + *(U+w*6+L) * *(U+Bz*6+L);
    double vBR = *(U+u*6+R) * *(U+Bx*6+R) + *(U+v*6+R) * *(U+By*6+R) + *(U+w*6+R) * *(U+Bz*6+R);
    double vBLs = *(U+u*6+Ls) * *(U+Bx*6+Ls) + *(U+v*6+Ls) * *(U+By*6+Ls) + *(U+w*6+Ls) * *(U+Bz*6+Ls);
    double vBRs = *(U+u*6+Rs) * *(U+Bx*6+Rs) + *(U+v*6+Rs) * *(U+By*6+Rs) + *(U+w*6+Rs) * *(U+Bz*6+Rs);

    *(U+e*6+Ls) = (SL-*(U+u*6+L))* *(U+e*6+L) - *(U+pT*6+L)* *(U+u*6+L) + pTs*SM + *(U+Bx*6+L) * (vBL-vBLs)/(SL-SM);
    *(U+e*6+Rs) = (SR-*(U+u*6+R))* *(U+e*6+R) - *(U+pT*6+R)* *(U+u*6+R) + pTs*SM + *(U+Bx*6+R) * (vBR-vBRs)/(SR-SM);

    // Alfven waveに対するjump条件
    double SRs = SM + fabs(*(U+Bx*6+R))/pow(*(U+rho*6+R), .5);
    double SLs = SM - fabs(*(U+Bx*6+L))/pow(*(U+rho*6+L), .5);

    *(U+rho*6+Lss) = *(U+rho*6+Ls);
    *(U+rho*6+Rss) = *(U+rho*6+Rs);

    double vss = (pow(*(U+rho*6+Ls), .5)* *(U+v*6+Ls)+pow(*(U+rho*6+Rs), .5)* *(U+v*6+Rs)+(*(U+By*6+Rs)-*(U+By*6+Ls))*sgn(*(U+Bx*6+L)))/(pow(*(U+rho*6+Ls), .5)+pow(*(U+rho*6+Rs), .5));
    double wss = (pow(*(U+rho*6+Ls), .5)* *(U+w*6+Ls)+pow(*(U+rho*6+Rs), .5)* *(U+w*6+Rs)+(*(U+Bz*6+Rs)-*(U+Bz*6+Ls))*sgn(*(U+Bx*6+L)))/(pow(*(U+rho*6+Ls), .5)+pow(*(U+rho*6+Rs), .5));
    double Byss = (pow(*(U+rho*6+Ls), .5)* *(U+By*6+Rs)+pow(*(U+rho*6+Rs), .5)* *(U+By*6+Ls) + pow(*(U+rho*6+Ls)* *(U+rho*6+Rs), .5)* (*(U+v*6+R)-*(U+v*6+L))*sgn(*(U+Bx*6+L)))/(pow(*(U+rho*6+Ls), .5)+pow(*(U+rho*6+Rs), .5));
    double Bzss = (pow(*(U+rho*6+Ls), .5)* *(U+Bz*6+Rs)+pow(*(U+rho*6+Rs), .5)* *(U+Bz*6+Ls) + pow(*(U+rho*6+Ls)* *(U+rho*6+Rs), .5)* (*(U+w*6+R)-*(U+w*6+L))*sgn(*(U+Bx*6+L)))/(pow(*(U+rho*6+Ls), .5)+pow(*(U+rho*6+Rs), .5));
    *(U+v*6+Lss) = vss;
    *(U+v*6+Rss) = vss;
    *(U+w*6+Lss) = wss;
    *(U+w*6+Rss) = wss;
    *(U+By*6+Lss) = Byss;
    *(U+By*6+Rss) = Byss;
    *(U+Bz*6+Lss) = Bzss;
    *(U+Bz*6+Rss) = Bzss;

    double vBss = SM* *(U+Bx*6+L)+vss*Byss+wss*Bzss;
    *(U+e*6+Lss) = *(U+e*6+Ls) - pow(*(U+rho*6+Ls), .5)*(vBLs - vBss)*sgn(*(U+Bx*6+L));
    *(U+e*6+Rss) = *(U+e*6+Rs) + pow(*(U+rho*6+Rs), .5)*(vBRs - vBss)*sgn(*(U+Bx*6+R));

    // fluxもとめていく
    int flux_index = 0;
    if(0 < SL){
        flux_index = L;
    }else if(0 < SLs){
        flux_index = Ls;
    }else if(0 < SM){
        flux_index = Lss;
    }else if(0 < SRs){
        flux_index = Rss;
    }else if(0 < SR){
        flux_index = Rs;
    }else{
        flux_index = R;
    }

    *(F+0) = *(U+rho*6+flux_index) * *(U+u*6+flux_index);
    *(F+1) = *(U+rho*6+flux_index) * pow(*(U+u*6+flux_index), 2) + *(U+pT*6+flux_index) - pow(*(U+Bx*6+flux_index), 2);
    *(F+2) = *(U+rho*6+flux_index) * *(U+v*6+flux_index) * *(U+u*6+flux_index) - *(U+Bx*6+flux_index) * *(U+By*6+flux_index);
    *(F+3) = *(U+rho*6+flux_index) * *(U+w*6+flux_index) * *(U+u*6+flux_index) - *(U+Bx*6+flux_index) * *(U+Bz*6+flux_index);
    *(F+4) = 0;
    *(F+5) = *(U+By*6+flux_index) * *(U+u*6+flux_index) - *(U+Bx*6+flux_index) * *(U+v*6+flux_index);
    *(F+6) = *(U+Bz*6+flux_index) * *(U+u*6+flux_index) - *(U+Bx*6+flux_index) * *(U+w*6+flux_index);
    *(F+7) = (*(U+e*6+flux_index) + *(U+pT*6+flux_index)) - *(U+Bx*6+flux_index) * (*(U+u*6+flux_index) * *(U+Bx*6+flux_index) + *(U+v*6+flux_index) * *(U+By*6+flux_index) + *(U+w*6+flux_index) * *(U+Bz*6+flux_index));
}

int main(void){
    double a=-0.5;         // 始点
    double b=0.5;          // 終点
    double dx=(b-a)/800.;  // 空間刻みの幅
    double nu=0.1;         // CFL数
    double dt=nu*dx/5;     // 時間刻みの幅
    int I=(b-a)/dx+1;      // 空間ステップ数
    int N=0.01/dt;         // 時間ステップ数

    double ans[I][8];    // 数値解を格納する配列
    double tmp[I][8];    // 一時的に格納

    // 初期条件の設定
    for(int i=0; i<I; i++){
        for(int index=0; index<8; index++){
            ans[i][index]=f(index, a+i*dx);
            tmp[i][index]=ans[i][index];
        }
    }

    for(int step=0; step<N; step++){
        double flux[I-1][8];
        double U[9][6]; // 中間状態を格納
        for(int i=0; i<I-1; i++){
            // 固定境界条件を課す
            int im = (int)fmax(0, i-1);
            int ip = (int)fmin(I-1, i+1);
            int ipp = (int)fmin(I-1, i+2);

            convert(&ans[i][0], &ans[ip][0], &U[0][0]);
            compute_flux(&U[0][0], &flux[i][0]);
        }
        for(int i=1; i<I-1; i++){
            for(int j=0; j<8; j++){
                ans[i][j] = ans[i][j] - dt/dx*(flux[i][j]-flux[i-1][j]);
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

    // ファイルへの書き込みrho, p, u, v, by
    for(int i=0; i<I; i++){
        double rho=ans[i][0];
        double u=ans[i][1]/rho;
        double v=ans[i][2]/rho;
        double w=ans[i][3]/rho;
        double bx=ans[i][4];
        double by=ans[i][5];
        double bz=ans[i][6];
        double B = bx*bx+by*by+bz*bz;
        double V = u*u+v*v+w*w;
        double e = ans[i][7];
        double p = (gamma-1)*(e-rho*V/2.-B/2.);
        
        fprintf(file, "%e, %e, %e, %e, %e, %e\n", a+i*dx, rho, p, u, v, by);
    }

    fclose(file);
    return 0;
}