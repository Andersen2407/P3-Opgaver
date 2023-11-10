from time import time
import random

i_amount = 200_000

s = [i for i in random.sample(range(0, i_amount), 100_000)]; s.sort()

#print(s)

missing = []

# Start time.
start_t = time()

i = 0; n = 0

# Algorithm
while(i < i_amount):
    if n < len(s):
        if i != s[n]:
            missing.append(i)
        else:
            n+=1
    else:
        missing.append(i)
    i+=1
    
# End time, print total time.
print(time()-start_t)
#print(missing)
