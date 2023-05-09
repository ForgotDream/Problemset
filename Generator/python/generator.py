import random

import cyaron

for d in range(1, 11):
    dataIO = cyaron.IO(file_prefix="A", data_id=d)
    n = 0
    m = 0
    if d in range(1, 3):
        n = 10
        m = 10
    elif d in range(3, 5):
        n = 100
        m = 100
    elif d in range(5, 7):
        n = 1000
        m = 1000
    elif d == 7:
        n = int(10 ** 7)
        m = 1
    elif d == 8:
        n = int(5 * 10 ** 6)
        m = 2
    elif d == 9:
        n = 20000
        m = 3500
    else:
        n = 1000
        m = 70000

    k = random.randint(1, m // 3)
    l = []

    for each in range(1, k + 1):
        l.append(cyaron.String.random(m))
    
    for each in l:
        

