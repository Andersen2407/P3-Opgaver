import random




def iter_randomized_selection(A, low, high, rank):
    while True:
    # Base case
        if low == high:
            return A[low]

        q = randomized_partition(A, low, high)
        k = q - low + 1
        if rank == k:
            return A[q]


        elif rank < k:
            # return rec_randomized_selection(A, low, q - 1, rank)
            high = q - 1
        else:
            # return rec_randomized_selection(A, q + 1, high, rank - k)
            low = q + 1
            rank = rank - k

def randomized_partition(A, low, high): # (list, low, high)
    randomI = random.randint(low, high) # pivot is last element
    A[randomI], A[high] = A[high], A[randomI]
    pivot = A[high]

    i = low - 1
    for j in range(low, high):
        if A[j] <= pivot:
            i += 1
            A[j], A[i] = A[i], A[j] # Exchange i with j.
            A[high], A[i+1] = A[i+1], A[high] # Exchange pivot with i
            return i+1

originalArray = [5, 4, 3, 2, 8, 10, 19, 18, 12]
print(originalArray)
rank = 9

A = originalArray[:]
i = iter_randomized_selection(A, 0, len(A)-1, rank)
print(f"Iter rank {rank} has value {i}")
print(A)