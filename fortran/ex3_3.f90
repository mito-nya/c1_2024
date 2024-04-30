  INTEGER :: n
  READ*, n
  IF(MOD(n, 400)==0) THEN
     PRINT*, 'uruu-doshi'
  ELSE IF(MOD(n, 100)==0) THEN
     PRINT*, 'hei-nen'
  ELSE IF(MOD(n, 4)==0) THEN
     PRINT*, 'uruu-doshi'
  ELSE
     PRINT*, 'hei-nen'
  END IF
END program
