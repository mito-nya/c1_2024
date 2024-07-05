#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

#define gamma 1.4

// 初期条件を配列uに入れる関数
double f(int i, double x){
    double rhoL=1.;
    double pL=1.;
    double vL=0.;
    double rhoR=0.125;
    double pR=0.1;
    double vR=0.;

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

// minmod関数を追記
double minmod(double x, double y){
    if(x*y > 0){
        if(fabs(x) < fabs(y)){
            return x;
        }else{
            return y;
        }
    }else{
        return 0;
    }
}

// superbee関数を追記
double superbee(double r){
    return fmax(0, fmax(fmin(2*r, 1), fmin(r, 2)));
}

int main(void){
    double a=-0.5;       // 始点
    double b=0.5;        // 終点
    double dx=1/127.;    // 空間刻みの幅
    double nu=0.7;       // CFL数
    double dt=nu*dx/5;   // 時間刻みの幅
    int I=(b-a)/dx+1;    // 空間ステップ数
    int N=0.20/dt;       // 時間ステップ数
    double k=-1.;        // MUSCLのfree parameter

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
            // 固定境界条件
            int ipp = (int)fmin(i+2, I-2);
            int ip = (int)fmin(i+1, I-2);
            int im = (int)fmax(i-1, 0);

            double rL[3];
            double rR[3];
            double uL[3];
            double uR[3];
            for(int j=0; j<3; j++){
                rL[j]=(u[ip][j]-u[i][j])/(u[i][j]-u[im][j]);
                rR[j]=(u[ip][j]-u[i][j])/(u[ipp][j]-u[ip][j]);
                uL[j]=u[i][j]+0.5*superbee(rL[j])*(u[i][j]-u[im][j]);
                uR[j]=u[ip][j]-0.5*superbee(rR[j])*(u[ipp][j]-u[ip][j]);
            }

            double rhoL = uL[0];
            double rhoR = uR[0];
            double vL = uL[1]/rhoL;
            double vR = uR[1]/rhoR;
            double EL = uL[2]/rhoL;
            double ER = uR[2]/rhoR;
            double pL=(gamma-1)*(rhoL*EL-rhoL*pow(vL, 2.)/2.);
            double pR=(gamma-1)*(rhoR*ER-rhoR*pow(vR, 2.)/2.);
            double HL=EL+pL/rhoL;
            double HR=ER+pR/rhoR;

            double brho=sqrt(rhoL*rhoR);
            double bv=(vL*sqrt(rhoL)+vR*sqrt(rhoR))/(sqrt(rhoL)+sqrt(rhoR));
            double bH=(HL*sqrt(rhoL)+HR*sqrt(rhoR))/(sqrt(rhoL)+sqrt(rhoR));

            double bcs=(gamma-1)*(bH-pow(bv, 2.)/2.);

            double lambda[3]={bv-bcs, bv, bv+bcs};

            double r[3][3]={{1, bv-bcs, bH-bv*bcs}, 
                            {1, bv, pow(bv, 2.)/2.}, 
                            {1, bv+bcs, bH+bv*bcs}}; 
            
            double drho=rhoR-rhoL;
            double dv=vR-vL;
            double dp=pR-pL;

            double parw[3];
            parw[0]=brho/2./bcs*(dp/brho/bcs-dv);
            parw[1]=drho-dp/pow(bcs, 2.);
            parw[2]=brho/2./bcs*(dp/brho/bcs+dv);

            double f0[3];
            f0[0]=rhoL*vL;
            f0[1]=rhoL*pow(vL, 2.)+pL;
            f0[2]=rhoL*HL*vL;
            
            double f1[3];
            f1[0]=rhoR*vR;
            f1[1]=rhoR*pow(vR, 2.)+pR;
            f1[2]=rhoR*HR*vR;

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
        double eps=p/rho/(gamma-1);

        fprintf(file, "%e, %e, %e, %e, %e, %e, %e\n", a+i*dx, rho, p, v, eps, v/cs, S);
    }

    fclose(file);
    
    return 0;
}