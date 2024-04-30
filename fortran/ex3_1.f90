  INTEGER :: n, s, k
  s=0; k=0
10  PRINT*, 'Input mark for each student (or negative one to quit): '
  READ*, n; IF(n<0) GOTO 999
  s=s+1
  IF(n>=60) k=k+1
  GOTO 10
999  PRINT*, k, 'students passed in this exam. total = ', s
  END
