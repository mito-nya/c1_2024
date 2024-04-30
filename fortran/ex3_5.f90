  INTEGER :: i, n1, n2, n3, n4
  n1=0; n2=0; n3=0; n4=0
1 READ*, i; IF(i<0 .OR. i>100) GOTO 9
  SELECT CASE(i)
  CASE(80:)
     PRINT*, 'A'; n1=n1+1
  CASE(70:79)
     PRINT*, 'B'; n2=n2+1
  CASE(60:69)
     PRINT*, 'C'; n3=n3+1
  CASE DEFAULT
     PRINT*, 'D'; n4=n4+1
  END SELECT
  GOTO 1
9 PRINT*, 'A=', n1, ' B=', n2, ' C=', n3, ' D=', n4
END program
