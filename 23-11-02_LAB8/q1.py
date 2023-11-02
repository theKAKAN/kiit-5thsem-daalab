import sys

NO_PARENT = -1

def dijkstra(adjacency_matrix, start_vertex):
    n_vertices = len(adjacency_matrix[0])

    # Default to Infinite
    shortest_distances = [sys.maxsize] * n_vertices
    added = [False] * n_vertices

    for vertex_index in range(n_vertices):
        shortest_distances[vertex_index] = sys.maxsize
        added[vertex_index] = False
        
    # Distance of source vertex from itself is always 0
    shortest_distances[start_vertex] = 0

    # Parent array to store shortest path tree
    parents = [-1] * n_vertices

    # Start has no parent
    parents[start_vertex] = NO_PARENT

    # Find shortest path for all 
    # vertices
    for i in range(1, n_vertices):
        # Pick the minimum distance vertex
        # from the set of vertices not yet
        # processed. nearest_vertex is 
        # always equal to start_vertex in 
        # first iteration.
        nearest_vertex = -1
        shortest_distance = sys.maxsize
        for vertex_index in range(n_vertices):
            if not added[vertex_index] and shortest_distances[vertex_index] < shortest_distance:
                nearest_vertex = vertex_index
                shortest_distance = shortest_distances[vertex_index]

        # Mark the picked vertex as
        # processed
        added[nearest_vertex] = True

        # Update dist value of the
        # adjacent vertices of the
        # picked vertex.
        for vertex_index in range(n_vertices):
            edge_distance = adjacency_matrix[nearest_vertex][vertex_index]
            
            if edge_distance > 0 and shortest_distance + edge_distance < shortest_distances[vertex_index]:
                parents[vertex_index] = nearest_vertex
                shortest_distances[vertex_index] = shortest_distance + edge_distance

    print_solution(start_vertex, shortest_distances, parents)


def print_solution(start_vertex, distances, parents):
    n_vertices = len(distances)
    print("Source\tDestination\tDistance\tPath")
    
    for vertex_index in range(n_vertices):
        print(start_vertex+1, "\t", vertex_index+1, "\t\t", distances[vertex_index], "\t\t", end="")
        print_path(vertex_index, parents)



def print_path(current_vertex, parents, callCount=0):
    if current_vertex == NO_PARENT:
        return
    print_path(parents[current_vertex], parents, callCount+1)
    if callCount == 0:
        print(current_vertex+1)
    else:
        print(str(current_vertex+1)+"->", end="")


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

dijkstra(graph, source)