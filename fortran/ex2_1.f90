  REAL :: a, b, av1, av2, av3
  READ *, a, b
  av1=(a+b)/2.0
  av2=(a*b)**0.5
  av3=2.0/(1.0/a+1.0/b)
  PRINT*, av1, av2, av3
END program

