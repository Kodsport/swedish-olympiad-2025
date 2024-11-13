def to_graphviz(n, edges):
    dot = "graph G {\n"
    
    # Add edges
    for (a, b) in edges:
        dot += f"    {a} -- {b};\n"
    
    dot += "}"
    return dot

n = int(input())

edges = []

# Each subsequent line represents an edge in the form "a b"
for i in range(n):
    a, b = map(int, input().split())
    edges.append((a, b))

graphviz_output = to_graphviz(n, edges)
print(graphviz_output)
