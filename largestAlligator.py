def largest_alligator(n, graph):
    """
    Returns the width of the largest alligator that can travel from pond 0 to pond n-1
    Parameters
    ------------
    n : int
        The number of ponds
    W : vector<vector<int>>
        The adjacency matrix of the swamp,
        W[i][j] represents the width of the channel between ponds i and j,
        or is 0 if there is no channel between those ponds
    ------------
    """
    source = 0 # Assume the source is the first node (according to question)
    maximum_width = 10**9

    num_vertices = len(graph)
    width = [-maximum_width] * num_vertices
    previous = [None] * num_vertices
    Q = set(range(num_vertices))

    width[source] = maximum_width

    while Q:
        u = max(Q, key=lambda v: width[v])
        Q.remove(u)

        if width[u] == float('-inf'):
            break

        for v in range(num_vertices):
            if graph[u][v] != 0:  # Check if there's an edge from u to v
                alt = max(width[v], min(width[u], graph[u][v]))
                if alt > width[v]:
                    width[v] = alt
                    previous[v] = u

    # Return the answer of nth node
    return width[n-1]

# Example usage:
n = 5
W = [
        [0, 0, 10, 6, 0],
        [0, 0, 8, 0, 9],
        [10, 8, 0, 0, 7],
        [6, 0, 0, 0, 0],
        [0, 9, 7, 0, 0]
    ]

result = largest_alligator(n, W)
print("Width of the largest alligator:", result)
