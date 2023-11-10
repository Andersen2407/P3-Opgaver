def greedy_alg(money):
    change = [25, 10, 5, 1]
    change_index = 0

    wallet = []
    while money > 0:
        if money >= change[change_index]:
            wallet.append(change[change_index])
            money -= change[change_index]
        elif change_index <= len(change):
            change_index+=1
                
    return wallet


wallet = greedy_alg(73)

print(wallet)

# → [25, 25, 10, 10, 1, 1, 1]
