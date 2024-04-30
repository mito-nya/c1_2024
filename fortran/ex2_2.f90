  REAL :: pi, r, h, v, s
  pi=3.14159265
  PRINT*, 'radius r and height h ?'
  READ*, r, h
  v=pi*h*r**2/3.
  s=pi*r*(r+(r**2+h**2)**0.5)
  PRINT*, 'Volume = ', v
  PRINT*, 'Surface Area = ', s
END program
