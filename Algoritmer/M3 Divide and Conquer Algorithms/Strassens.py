import numpy as np
import time


# Function for fetching the 4 square submatrices of a square matrix
def ID(Y, i1, i2):
   n = len(Y)
   if i1==1 and i2==1:   return Y[0:n//2:1, 0:n//2:1]    # top left
   elif i1==1 and i2==2: return Y[0:n//2:1, n//2:n:1]    # top right
   elif i1==2 and i2==1: return Y[n//2:n:1, 0:n//2:1]    # bottom left
   elif i1==2 and i2==2: return Y[n//2:n:1, n//2:n:1]    # bottom right




def STRASSENS(A, B, n):
   """
   Just think about it, it is self explanatory :)
   """
   if n==1: return A * B
  
   if len(A) % 2 != 0: raise Exception
  
   C11 = STRASSENS((ID(A,1,1)+ID(A,2,2)),(ID(B,1,1)+ID(B,2,2)), n/2)    +   STRASSENS(ID(A,2,2), (ID(B,2,1)-ID(B,1,1)),n/2)    -    STRASSENS((ID(A,1,1)+ID(A,1,2)),ID(B,2,2), n/2)   +     STRASSENS((ID(A,1,2)-ID(A,2,2)),(ID(B,2,1)+ID(B,2,2)), n/2)
   C12 = STRASSENS(ID(A, 1, 1), (ID(B, 1, 2) - ID(B, 2, 2)), n/2) + STRASSENS((ID(A, 1, 1) + ID(A, 1, 2)), ID(B, 2, 2), n/2)
   C21 = STRASSENS((ID(A,2,1)+ID(A,2,2)), ID(B,1,1), n/2) + STRASSENS(ID(A,2,2), (ID(B,2,1)-ID(B,1,1)), n/2)
   C22 = STRASSENS((ID(A,1,1)+ID(A,2,2)), ((ID(B,1,1))+ID(B,2,2)), n/2) + STRASSENS(ID(A,1,1), (ID(B,1,2)-ID(B,2,2)), n/2) - STRASSENS((ID(A,2,1) + ID(A,2,2)), ID(B, 1, 1), n/2) - STRASSENS((ID(A,1,1)-ID(A,2,1)), (ID(B, 1, 1) + ID(B, 1, 2)), n/2)
  
   cUpper = np.concatenate((C11, C12), axis=1)
   cLower = np.concatenate((C21, C22), axis=1)
   C = np.concatenate((cUpper, cLower), axis=0)
   return C


# Opgave 2
A = np.array([
   [6, 4, 9, 8],
   [5, 5, 1, 2],
   [2, 3, 1, 6],
   [0, 8, 4, 4]])


B = np.array([
   [4, 4, 2, 5],
   [2, 8, 1, 2],
   [1, 5, 0, 2],
   [7, 5, 3, 9]])


n = 4
A = np.arange(n**2).reshape(n,n)
B = np.arange(n**2).reshape(n,n)


start = time.time()
opgave2 = np.matmul(A, B)  #Den fra opgaven
print("OPGAVE2", time.time()-start)
#print(opgave2)


start = time.time()
stras = STRASSENS(A, B, len(A))
print("STRASSENS", time.time()-start)
#print(stras)
