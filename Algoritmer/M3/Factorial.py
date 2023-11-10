import time
import sys


sys.setrecursionlimit(10**8)    # :|


def fact(n):
   if n == 0: return 1
   if n == 1: return 1
   return n*fact(n-1)


n = 10**6
tries = 1
print(n)
times = []
for i in range(tries):        #take average
   start = time.time()
   a = fact(n)
   times.append(time.time()-start)


print("\nAverage time", sum(times)/tries)