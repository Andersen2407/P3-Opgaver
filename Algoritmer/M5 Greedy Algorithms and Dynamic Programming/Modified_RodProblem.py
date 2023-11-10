def modified_rod(p,n,c):

    # Let r be a new array from 0 to n and s from 1 to n
    r = [0]*n
    s = [1]*n

    for j in range(1,n+1):
        q = -float('inf')
        for i in range(1,j+1):
            cuts = -1
            k=n
            while k>0:
                cuts+=1
                k=k-s[k-1]
            cost = c*cuts
            print('cuts=',cuts)

            if q < p[i-1]+r[j-i-1]-cost:
                q = p[i-1]+r[j-i-1]-cost
                s[j-1]=i
        r[j-1] = q
    return (r,s)

def print_modrod(p,n,c):
    (r,s) = modified_rod(p,n,c)

    print(max(r))
    cuts = -1
    while n>0:
        cuts+=1
        print(s[n-1],end='-')
        n=n-s[n-1]
    print('')
    print(cuts)

p = [1,5,8,9,10,17,17,20,24,25,28,27,27]
print_modrod(p,13,1)
