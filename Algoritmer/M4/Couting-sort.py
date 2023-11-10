import random
import time


def counting_sort(A, n, k):
    B = [0] * n
    C = [0] * (k + 1)

    for i in range(n):
        C[A[i]] += 1

    for i in range(1, k + 1):
        C[i] += C[i - 1]

    for i in reversed(range(n)):
        B[C[A[i]] - 1] = A[i]
        C[A[i]] -= 1

    return B


if __name__ == "__main__":
    n = 5
    size = 10 ** n
    times=[]


    for _ in range(100):
        A = [random.randint(1, 100) for i in range(0, size)]
        length = len(A)


    start_time = time.time()
    counting_sort(A, length, max(A))
    end_time = time.time()


    times.append(end_time-start_time)


    # print("Sorted\n", sorted)
    print(f"Time: {sum(times) / len(times)}")