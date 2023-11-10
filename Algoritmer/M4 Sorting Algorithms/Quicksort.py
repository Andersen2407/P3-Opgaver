import sys


sys.setrecursionlimit(10**8)


def partition(A, low, high):     #(list, low, high)
    pivot = A[high]                # pivot is last element
    i = low - 1
   
    for j in range(low, high):
        if A[j] <= pivot:
            i += 1
            A[j], A[i] = A[i], A[j]          # Exchange i with j.
       
    A[high], A[i+1] = A[i+1], A[high]       # Exchange pivot with i
    return i+1


def quick_sort(A, low, high):
    if low < high:
        q = partition(A, low, high)
        quick_sort(A, low, q-1)
        quick_sort(A, q+1, high)




if __name__ == "__main__":
    import random
    import time


    A = [random.randint(1, 100) for i in range(0, 200000)]
    # A = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
    length = len(A)
    #print("Initial=", A, "is", length, "long")


    # Time it
    start_time = time.time()
    quick_sort(A, 0, length-1)
    end_time = time.time()


    #print("Sorted =", A)
    print(f"Time: {end_time-start_time}")