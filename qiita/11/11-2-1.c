// imlicit

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265

double f(double x){
    return exp(-1*(x-.5)*(x-.5)/.25);
}

// LU分解するだけ
void LU(int I, double *Apt, double *Lpt, double *Upt){
    for(int i=0; i<I; i++){
        for(int j=0; j<I; j++){
            if(i==0 && j==0){
                *(Upt+i*I+j)=*(Apt+i*I+j);
                *(Lpt+i*I+j)=1.;
            }else if(i==0 && j>0){
                *(Upt+i*I+j)=*(Apt+i*I+j);
                *(Lpt+i*I+j)=0.;
            }else if(i>0 && j==0){
                *(Upt+i*I+j)=*(Apt+i*I+j)/ *(Upt);
                *(Lpt+i*I+j)=0.;
            }else if(i==j && j>0){
                double tmp=0.;
                for(int k=0; k<i; k++) tmp=tmp+ *(Lpt+i*I+k)* *(Upt+k*I+j);
                *(Upt+i*I+j)=*(Apt+i*I+j)-tmp;
                *(Lpt+i*I+j)=1.;
            }else if(i>j && j>0){
                double tmp=0.;
                for(int k=0; k<j; k++) tmp=tmp+ *(Lpt+i*I+k)* *(Upt+k*I+j);
                *(Upt+i*I+j)=0.;
                *(Lpt+i*I+j)=(*(Apt+i*I+j)-tmp)/ *(Upt+j*I+j);
            }else if(i<j && i>0){
                double tmp=0.;
                for(int k=0; k<i; k++) tmp=tmp+ *(Lpt+i*I+k)* *(Upt+k*I+j);
                *(Lpt+i*I+j)=0.;
                *(Upt+i*I+j)=*(Apt+i*I+j)-tmp;
            }
        }
    }
}

// 解くだけ
void solve(double a, double dx, double dt, int I, int N, double *Lpt, double *Upt, double *upt, double funcpt(double x)){
    // 初期条件
    for(int i=0;i<I;i++){
        *(upt+i*N+0)=funcpt(a+i*dx);
    }

    double c=dx*dx/dt;

    // 左の列から埋めていく
    for(int t=1; t<N; t++){
        // Ly=b
        for(int i=0;i<I;i++){
            *(upt+i*N+t)=c* *(upt+i*N+t-1);
        }
        for(int j=0;j<I-1;j++){
            for(int i=j+1;i<I; i++){
                *(upt+i*N+t) -= *(upt+j*N+t) * *(Lpt+i*I+j);
            }
        }
        // Lx=y
        for(int j=I-1;j>=0;j--){
            *(upt+j*N+t) /= *(Upt+j*I+j);
            for(int i=0;i<=j-1; i++){
                *(upt+i*N+t) -= *(upt+j*N+t) * *(Upt+i*I+j);
            }
        }
    }
}

// 出力するだけ
void out(double a, double dx, int I, int N, double *upt){
    for(int i=0;i<I; i++){
        printf("%e, ", a+i*dx);
        for(int j=0; j<N-1; j++){
            printf("%e, ", *(upt+i*N+j));
        }
        printf("%e\n", *(upt+i*N+N-1));
    }
}

void debug(int M, int N, double *mpt){
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            printf("%e ", *(mpt+i*N+j));
        }
        printf("\n");
    }
}


// int main(void){
//     int I=10;
//     int N=10;
//     double a=-1.;
//     double b=2.;
//     double dt=1.e-5;
//     double dx=(b-a)/(I+0.);
//     double A[I][I];

//     // Aの定義
//     for(int i=0;i<I;i++){
//         for(int j=0;j<I;j++){
//             A[i][j]=0.;
//         }
//     }
//     A[0][0]=dx*dx/dt;
//     for(int i=1;i<I-1;i++){
//         A[i][i-1]=-1.;
//         A[i][i]=2.+dx*dx/dt;
//         A[i][i+1]=-1.;
//     }
//     A[I-1][I-1]=dx*dx/dt;

//     double L[I][I];
//     double U[I][I];
//     LU(I, &A[0][0], &L[0][0], &U[0][0]);

//     debug(I, I, &L[0][0]);
//     printf("\n");
//     debug(I, I, &U[0][0]);

//     double u[I][N];
//     solve(a, dx, dt, I, N, &L[0][0], &U[0][0], &u[0][0], f);
    
//     // out(a, dx, I, N, &u[0][0]);

//     // debug(I, I, &A[0][0]);
//     return 0;
// }

int main(void){
    double A[2][2]={{1., 2.}, {3., 1.}};
    double L[2][2]={{0., 0.}, {0., 0.}};
    double U[2][2]={{0., 0.}, {0., 0.}};
    LU(2, &A[0][0], &L[0][0], &U[0][0]);
    debug(2, 2, &L[0][0]);
    printf("\n");
    debug(2, 2, &U[0][0]);
}