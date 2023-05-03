import random

import cyaron

for d in range(1, 11):
    data = cyaron.IO(file_prefix = "C", data_id = d)

    n = 0
    m = 0
    if d == 1:
        n, m = 1, 0
    elif d <= 3:
        n = random.randint(0, 50) + 50 
        m = random.randint(0, 50) + 50
    elif d <= 6:
        n = random.randint(0, 2.5 * (10 ** 3)) + 2.5 * (10 ** 3)
        m = random.randint(0, 2.5 * (10 ** 3)) + 2.5 * (10 ** 3)
    else:
        n = random.randint(0, 10 ** 5) + 10 ** 5 
        m = random.randint(0, 10 ** 5) + 10 ** 5
    
    n = int(n)
    m = int(m)

    g = 0
    if d == 7:
        g = cyaron.Graph.chain(n)
    elif d == 8:
        g = cyaron.Graph.flower(n)
    else:
        d1 = 1
        d2 = 1
        while d1 + d2 >= 1:
            d1 = random.random()
            d2 = random.random()
        g = cyaron.Graph.tree(n, d1, d2)
    
    data.input_writeln()