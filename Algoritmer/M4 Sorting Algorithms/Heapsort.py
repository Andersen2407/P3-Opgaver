import random
import time


def max_heapify(A, i):
    l = 2*i+1 # index of left node
    r = 2*i+2 # index of right node


    if l <= len(A)-1: # fixes 0-indexing
        if A[l] > A[i]:
            largest = l
        else:
            largest = i
    else:
        largest = i

    if r <= len(A)-1: # fixes 0-indexing
        if A[r] > A[largest]:
            largest = r


    if largest != i:
        A[i], A[largest] = A[largest], A[i]
        max_heapify(A, largest)




def build_max_heap(A, n):
    for i in reversed(range(0, n//2)):
        max_heapify(A, i)


def heap_sort(A: list, n):
    build_max_heap(A, n)
    sortedA = []
    for i in reversed(range(2-2, n)): # (2-2) fixed 0-indexing
        A[0], A[i] = A[i], A[0]
    # appends last element to the sorted list
    sortedA.append(A.pop())
    max_heapify(A, 0)

    return sortedA


if __name__ == "__main__":
    n = 5
    size = 10 ** n
    times=[]


    for _ in range(100):
        A = [random.randint(1, 100) for i in range(0, size)]
        length = len(A)


    start_time = time.time()
    heap_sort(A, length)
    end_time = time.time()


    times.append(end_time-start_time)


    # print("Sorted\n", sorted)
    print(f"Time: {sum(times) / len(times)}")