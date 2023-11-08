import time

def horner(A, n, x):
   p = 0
   for i in range(n, -1, -1):
       p = A[i] + x * p
   return p

def naive_polynomial_evaluation(coefficients, x):
   result = 0
   n = len(coefficients)
   for i in range(n - 1):
       result += coefficients[i] * (x**i)
   return result

starttime = time.time()

for _ in range(100):
   horner([i for i in range(11)], 10, 1)
   horner([i for i in range(101)], 100, 1)
   horner([i for i in range(1001)], 1000, 1)

endtime = time.time()
print(endtime - starttime)  # 0.00562596... in seconds

starttime = time.time()

for _ in range(100):
   naive_polynomial_evaluation([i for i in range(11)], 10)
   naive_polynomial_evaluation([i for i in range(101)], 100)
   naive_polynomial_evaluation([i for i in range(1001)], 1000)

endtime = time.time()
print(endtime - starttime)  # 0.4579083... in seconds