def change_alg(money, k_change_set):
    optimal_solutions = [0] * (money + 1)

    for m in range(1, money + 1):
        min_coins = float('inf')

        for change_val in k_change_set:
            if m >= change_val:
                min_coins = min(min_coins, optimal_solutions[m - change_val] + 1)

        optimal_solutions[m] = min_coins
    return optimal_solutions[money]

# Example usage:
k_change_set = [1, 8, 16, 25]
money = 40
result = change_alg(money, k_change_set)
print(f"Minimum number of coins to make change for {money} is {result}")
