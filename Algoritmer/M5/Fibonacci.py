def fibonacci(n):
    fib = [0,1]
    # Check base-case
    if n < len(fib):
        return fib[n]

    # Iterate through until n.
    for i in range(2, n):
        fib.append(fib[i-1]+fib[i-2])
    return fib[n-1]

print(fibonacci(10))
#  → prints: 34