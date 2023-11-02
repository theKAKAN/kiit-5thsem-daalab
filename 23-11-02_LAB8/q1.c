#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

int graph[MAX_VERTICES][MAX_VERTICES];
int dist[MAX_VERTICES];
int visited[MAX_VERTICES];

int dijkstra(int start, int end, int n) {
    int i, j, u, v, min_dist;
    for (i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[start] = 0;
    for (i = 1; i <= n; i++) {
        min_dist = INT_MAX;
        for (j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        visited[u] = 1;
        for (v = 1; v <= n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    return dist[end];
}

void print_path(int start, int end, int n) {
    int i, j, u, v, min_dist;
    int path[MAX_VERTICES];
    int path_count = 0;
    for (i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[start] = 0;
    for (i = 1; i <= n; i++) {
        min_dist = INT_MAX;
        for (j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        visited[u] = 1;
        for (v = 1; v <= n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    printf("Source Destination Cost Path\n");
    for (i = 1; i <= n; i++) {
        if (i != start) {
            printf("%d\t%d\t", start, i);
            if (dist[i] != INT_MAX) {
                printf("%d\t", dist[i]);
                path_count = 0;
                path[path_count] = i;
                j = i;
                while (j != start) {
                    path_count++;
                    j = visited[j];
                    path[path_count] = j;
                }
                printf("%d", path[path_count]);
                for (j = path_count - 1; j >= 0; j--) {
                    printf("->%d", path[j]);
                }
            } else {
                printf("INF\t-");
            }
            printf("\n");
        }
    }
}

int main() {
    int n, start, i, j;
    FILE *fp;
    fp = fopen("inDiAdjMat1.dat", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    fscanf(fp, "%d", &n);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            fscanf(fp, "%d", &graph[i][j]);
        }
    }
    fclose(fp);
    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);
    printf("Enter the Source Vertex: ");
    scanf("%d", &start);
    dijkstra(start, n, n);
    print_path(start, n, n);
    return 0;
}
