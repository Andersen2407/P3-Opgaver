import numpy as np
import time


# Function for fetching the 4 square submatrices of a square matrix
def ID(Y, i1, i2):
    n = len(Y)
    if i1==1 and i2==1:   return Y[0:n//2, 0:n//2]    # top left
    elif i1==1 and i2==2: return Y[0:n//2, n//2:n]    # top right
    elif i1==2 and i2==1: return Y[n//2:n, 0:n//2]    # bottom left
    elif i1==2 and i2==2: return Y[n//2:n, n//2:n]    # bottom right




def MATRIX_MULTIPLY_RECURSIVE(A, B, n):
    #print(n)
    if n == 1:
        return A * B
   
    if n % 2 == 1:  # If ODD length, pad to be even!
        A = np.pad(A, ((0,1), (0,1))) # Pads bottom and right   ((top, bottom), (left, right))
        B = np.pad(B, ((0,1), (0,1))) # Pads bottom and right   ((top, bottom), (left, right))


    submatrixSize = (n+1)//2    # Calculate size of submatrices whether padded or not!
    # E.g. n=3  -> n=2
    # E.g. n=4  -> n=2
    # E.g. n=5  -> n=3
    # E.g. n=6  -> n=3


    C11 = MATRIX_MULTIPLY_RECURSIVE(ID(A, 1, 1), ID(B, 1, 1), submatrixSize) + MATRIX_MULTIPLY_RECURSIVE(ID(A, 1, 2), ID(B, 2, 1), submatrixSize)
    C12 = MATRIX_MULTIPLY_RECURSIVE(ID(A, 1, 1), ID(B, 1, 2), submatrixSize) + MATRIX_MULTIPLY_RECURSIVE(ID(A, 1, 2), ID(B, 2, 2), submatrixSize)
    C21 = MATRIX_MULTIPLY_RECURSIVE(ID(A, 2, 1), ID(B, 1, 1), submatrixSize) + MATRIX_MULTIPLY_RECURSIVE(ID(A, 2, 2), ID(B, 2, 1), submatrixSize)
    C22 = MATRIX_MULTIPLY_RECURSIVE(ID(A, 2, 1), ID(B, 1, 2), submatrixSize) + MATRIX_MULTIPLY_RECURSIVE(ID(A, 2, 2), ID(B, 2, 2), submatrixSize)


    cUpper = np.concatenate((C11, C12), axis=1)
    cLower = np.concatenate((C21, C22), axis=1)
    C = np.concatenate((cUpper, cLower), axis=0)


    #return C
    return C[:n, :n]      #Remove padding if padded earlier




# Data test!
n = 6                  # 2^n = bestcase (aldrig paddes)       (2^n)+1 = worstcase (paddes hvert step)
A = np.arange(n**2).reshape(n,n)
B = np.arange(n**2).reshape(n,n)


start = time.time()
data = np.matmul(A, B)
print("Numpy", time.time()-start)
#print(data)


print("_"*50+"\n")


start = time.time()
matrixmultiply = MATRIX_MULTIPLY_RECURSIVE(A, B, len(A))
print("Recursive matrix multiplier", time.time()-start)
print(matrixmultiply)