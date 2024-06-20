program main
    implicit none

    ! r方向の刻み
    INTEGER, parameter :: jmax = 200
    ! 時間ステップ数
    INTEGER, parameter :: nmax = 10000000
    ! 出力時間ステップ
    INTEGER, parameter :: nint = 10000

    REAL, dimension(0:jmax) :: u
    REAL, dimension(1:jmax-1) :: unew
    REAL delx, delt, r, x

    INTEGER j,n
    INTEGER i

    CHARACTER(len = 20) fname

    i = 0

    delx = 1.0 / real(jmax)
    delt = (delx**2) /3
    ! クーラン数
    r = delt / delx*2

    !初期条件
    u(0) = 0.0
    DO j = 1, jmax-1
        x = real(j)*delx
        u(j) = x*exp(-(x/0.1)**2)
    END DO
    u(jmax) = 0.0 
    DO n = 0, nmax
        IF (mod(n, nint) == 0) THEN
            write(fname,'(i5.5,a)') , i, '.dat'
            open(10, file = fname)
            DO j = 1, jmax
                x = real(j)*delx
                ! 元々の変数に変換して出力
                write(10,'(2f12.5, 2f12.5), 2f12.10)') x**2, u(j)/(x**3), u(j)/(x**2)
            END DO
            CLOSE(10)
            i = i + 1
        END IF

        ! 拡散方程式の差分方程式
        DO j = 1, jmax-1
            unew(j) = u(j+1)*r + u(j)*(1.0 - r*2.0) + u(j-1)*r
        END DO

        ! 値の更新
        DO j = 1, jmax-1
            u(j) = unew(j)
        END DO
    END DO

END program main