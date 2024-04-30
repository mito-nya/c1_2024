  REAL :: x
  PRINT*, 'Input: '
  READ*, x
  IF(x>=0.) THEN
     PRINT*, SQRT(x)
  ELSE
     PRINT*, 'Impossible for x<0.'
  END IF
END program
