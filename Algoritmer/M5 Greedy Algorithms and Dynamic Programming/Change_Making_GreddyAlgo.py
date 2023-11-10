def greedy_alg(money, c, k):
    change = [c**power for power in range(k+1)]
    print(change)

    change_index = 0
    wallet = []
    while money > 0:
        change_index = change.index(max(change))
        
        if money >= change[change_index]:
            wallet.append(change[change_index])
            money -= change[change_index]
        else:
            change.remove(change[change_index])

    return wallet

money = 20
wallet = greedy_alg(money, 5, 4)
print(money, wallet)
