#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    // File reading
    FILE* ptr = fopen("numbers_q3.txt", "r");

    int ar[n];
    for( int i = 0; i < n; i++ )
        fscanf(ptr, "%d", &ar[i]);
    fclose(ptr);

    int totalDupes = 0;
    for( int i = 0; i < n-1; i++ ){
        for( int j = i + 1; j < n; j++ ){
            if( ar[i] == ar[j] ){
                totalDupes++;
                break;
            }
        }
    }

    int maxDupe = 0, maxFreq = 0;

    for( int i = 0; i < n; i++ ){
        int count = 0;
        for( int j = i; j < n; j++ ){
            if( ar[i] == ar[j] )
                count++;
        }

        if( count > maxDupe ){
            maxDupe = count;
            maxFreq = ar[i];
        }
    }

    printf("Total no. of duplicates: %d\n", totalDupes);
    printf("Most repeating element is %d, repeated %d times.\n", maxFreq, maxDupe);
    return 0;
}