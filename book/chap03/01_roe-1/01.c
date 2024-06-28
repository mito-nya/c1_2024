#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

#define gamma 1.4

double f(int i, double x){
    double rhoL=1.;
    double pL=1.;
    double vL=0.9;
    double rhoR=0.125;
    double pR=0.1;
    double vR=0.9;

    if(i==0){ // rho
        if(x<0) return rhoL;
        else return rhoR;
    }else if(i==1){ // rho*v
        if(x<0) return vL*f(0, x);
        else return vR*f(0, x);
    }else if(i==2){ // rho*E
        if(x<0) return pL/(gamma-1)+pow(f(1, x), 2.)/2./f(0, x);
        else return pR/(gamma-1)+pow(f(1, x), 2.)/2./f(0, x);
    }
    else{
        exit(1);
    }
}

int main(void){
    double a=-0.5;       // 始点
    double b=0.5;        // 終点
    double dx=1/128.;    // 空間刻みの幅
    double nu=0.7;       // CFL数
    double dt=nu*dx/5;   // 時間刻みの幅
    int I=(b-a)/dx+1;    // 空間ステップ数
    int N=0.15/dt;       // 時間ステップ数

    double u[I][3];      // 数値解を格納する配列
    double tmp[I][3];    // 一時的に格納

    // 初期条件の設定
    for(int i=0; i<I; i++){
        for(int index=0; index<3; index++){
            u[i][index]=f(index, a+i*dx);
            tmp[i][index]=u[i][index];
        }
    }

    for(int step=0; step<N; step++){
        // 解くパート
        // 固定境界条件を課す
        // fluxを求める
        double flux[I-1][3];
        for(int i=0; i<I-1; i++){
            double rho0=u[i][0];
            double rho1=u[i+1][0];
            double v0=u[i][1]/rho0;
            double v1=u[i+1][1]/rho1;
            double E0=u[i][2]/rho0;
            double E1=u[i+1][2]/rho1;
            double p0=(gamma-1)*(rho0*E0-rho0*pow(v0, 2.)/2.);
            double p1=(gamma-1)*(rho1*E1-rho1*pow(v1, 2.)/2.);
            double H0=E0+p0/rho0;
            double H1=E1+p1/rho1;

            double brho=sqrt(rho0*rho1);
            double bv=(v0*sqrt(rho0)+v1*sqrt(rho1))/(sqrt(rho0)+sqrt(rho1));
            double bH=(H0*sqrt(rho0)+H1*sqrt(rho1))/(sqrt(rho0)+sqrt(rho1));

            double bcs=(gamma-1)*(bH-pow(bv, 2.)/2.);

            double lambda[3]={bv-bcs, bv, bv+bcs};

            double r[3][3]={{1, bv-bcs, bH-bv*bcs}, 
                            {1, bv, pow(bv, 2.)/2.}, 
                            {1, bv+bcs, bH+bv*bcs}}; 
            
            double drho=rho1-rho0;
            double dv=v1-v0;
            double dp=p1-p0;

            double parw[3];
            parw[0]=brho/2./bcs*(dp/brho/bcs-dv);
            parw[1]=drho-dp/pow(bcs, 2.);
            parw[2]=brho/2./bcs*(dp/brho/bcs+dv);

            double f0[3];
            f0[0]=rho0*v0;
            f0[1]=rho0*pow(v0, 2.)+p0;
            f0[2]=rho0*H0*v0;

            double f1[3];
            f1[0]=rho1*v1;
            f1[1]=rho1*pow(v1, 2.)+p1;
            f1[2]=rho1*H1*v1;

            for(int j=0; j<3; j++){
                double tmpf=0;
                for(int k=0; k<3; k++){
                    tmpf += fabs(lambda[k])*parw[k]*r[k][j];
                }
                flux[i][j]=(f0[j]+f1[j]-tmpf)/2.;
            }            
        }

        for(int i=0; i<I-2; i++){
            for(int j=0; j<3; j++){
                tmp[i+1][j]=u[i+1][j]-dt/dx*(flux[i+1][j]-flux[i][j]);
            }
        }

        for(int i=0; i<I; i++){
            for(int j=0; j<3; j++){
                u[i][j]=tmp[i][j];
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

    // ファイルへの書き込み
    for(int i=0; i<I; i++){
        double rho=u[i][0];
        double v=u[i][1]/rho;
        double E=u[i][2]/rho;
        double p=(gamma-1)*(rho*E-rho*pow(v, 2.)/2.);
        double H=E+p/rho;
        double cs=(gamma-1)*(H-pow(v, 2.)/2.);
        double S=log(p/pow(rho, gamma));

        fprintf(file, "%e, %e, %e, %e, %e\n", a+i*dx, rho, v/cs, S, v-cs);
    }

    fclose(file);
    
    return 0;
}