import cyaron

n = 5
m = 10

data = cyaron.IO(file_prefix="tmp")

data.input_writeln(n, m, 2)

graph = cyaron.Graph.UDAG(n, m)
data.input_writeln(graph.to_str(output=cyaron.Edge.unweighted_edge))
