IMPLICIT NONE
  REAL :: x, f
  PRINT*, 'x?'
  READ*, x
  IF(x<28.) THEN
     f=0.
  ELSE IF(x<30.) THEN
     f=0.5*x-14.
  ELSE IF(x<32.) THEN
     f=-0.5*x+16.
  ELSE
     f=0.
  END IF
  PRINT*, x, f
END program
