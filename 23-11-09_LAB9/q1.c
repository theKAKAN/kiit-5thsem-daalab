#include <stdio.h>
#include <limits.h>

void matrixChainMultiplication(int dims[], int n) {
    int M[n][n]; // M-Table
    int S[n][n]; // S-Table

    for (int i = 1; i < n; i++) {
        M[i][i] = 0;
    }

    for (int chainLen = 2; chainLen < n; chainLen++) {
        for (int i = 1; i < n - chainLen + 1; i++) {
            int j = i + chainLen - 1;
            M[i][j] = INT_MAX; // Initialize to a large value

            for (int k = i; k <= j - 1; k++) {
                int cost = M[i][k] + M[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (cost < M[i][j]) {
                    M[i][j] = cost;
                    S[i][j] = k;
                }
            }
        }
    }

    printf("M Table:\n");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i <= j) {
                printf("%d\t", M[i][j]);
            } else {
                printf("0\t");
            }
        }
        printf("\n");
    }

    printf("S Table:\n");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i < j) {
                printf("%d\t", S[i][j]);
            } else {
                printf("0\t");
            }
        }
        printf("\n");
    }

    // Print the optimal parenthesization
    printf("Optimal parenthesization: ");
    int optimalOrder[100];
    int count = 0;

    int i = 1;
    int j = n - 1;
    optimalOrder[count++] = i;

    while (i < j) {
        i = S[i][j] + 1;
        optimalOrder[count++] = i;
    }

    i = 0;
    while (i < count) {
        if (i == count - 1) {
            printf("A%d", optimalOrder[i]);
        } else {
            printf("(A%d ", optimalOrder[i]);
        }
        i++;
    }

    for (i = 0; i < count - 1; i++) {
        printf(")");
    }

    printf("\n");
    printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", M[1][n - 1]);
}

int main() {
    int n;
    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int dims[n + 1];

    printf("Enter dimensions of the matrices:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter row and column size of A%d: ", i+1);
        scanf("%d %d", &dims[i], &dims[i + 1]);
    }

    matrixChainMultiplication(dims, n + 1);
    return 0;
}
