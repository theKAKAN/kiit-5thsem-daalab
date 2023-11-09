#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

void longest_common_subsequence(char *str1, char *str2) {
    int m = strlen(str1);
    int n = strlen(str2);

    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Print the LCS
    int lcs_length = dp[m][n];
    char lcs[lcs_length + 1];
    lcs[lcs_length] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            lcs[--lcs_length] = str1[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    printf("Longest Common Subsequence: %s\n", lcs);
    printf("Length of Longest Common Subsequence: %d\n", dp[m][n]);
}

int main() {
    char str1[100];
    char str2[100];

    printf("Enter str1: ");
    scanf("%s", str1);
    printf("Enter str2: ");
    scanf(" %s", str2);

    longest_common_subsequence(str1, str2);

    return 0;
}
