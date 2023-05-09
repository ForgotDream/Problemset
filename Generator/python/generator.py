import random

import cyaron

for d in range(1, 11):
    n = random.randint(1, 200000)
    data = cyaron.IO(file_prefix = "A", data_id = d)
    str = cyaron.String.random(n)
    data.input_writeln(str)
