import random

import cyaron

for d in range(1, 11):
    dataIO = cyaron.IO(file_prefix="A", data_id=d)
    n = 100000
    m = 200000

    g = cyaron.Graph.graph(n, m, directed = False)