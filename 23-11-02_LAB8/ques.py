import sys

# Function to find the vertex with the minimum distance value
def min_distance(dist, visited):
    min_dist = sys.maxsize
    min_vertex = -1
    for v in range(len(dist)):
        if dist[v] < min_dist and not visited[v]:
            min_dist = dist[v]
            min_vertex = v
    return min_vertex

# Function to print the shortest path from source to destination
def print_path(parent, j):
    if parent[j] == -1:
        return str(j)
    return print_path(parent, parent[j]) + " -> " + str(j)

# Function to implement Dijkstra's algorithm
def dijkstra(graph, source, num_vertices):
    dist = [sys.maxsize] * num_vertices
    parent = [-1] * num_vertices
    dist[source] = 0
    visited = [False] * num_vertices

    for _ in range(num_vertices - 1):
        u = min_distance(dist, visited)
        visited[u] = True
        for v in range(num_vertices):
            if not visited[v] and graph[u][v] > 0 and dist[u] + graph[u][v] < dist[v]:
                dist[v] = dist[u] + graph[u][v]
                parent[v] = u

    print("Source Destination Cost Path")
    for i in range(num_vertices):
        if i != source:
            print(f"{source + 1}\t{i + 1}\t{dist[i]}\t{print_path(parent, i)}")

# Read the input graph from the file
try:
    with open("inDiAdjMat1.dat", "r") as file:
        lines = file.readlines()
        num_vertices = len(lines)
        graph = [[int(cost) for cost in line.split()] for line in lines]
except FileNotFoundError:
    print("Input file not found.")
    sys.exit(1)

# Get user input for the source vertex
num_vertices = len(graph)
source = int(input("Enter the Source Vertex: ")) - 1

if source < 0 or source >= num_vertices:
    print("Invalid source vertex.")
    sys.exit(1)

dijkstra(graph, source, num_vertices)
