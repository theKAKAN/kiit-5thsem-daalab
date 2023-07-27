#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    // File reading
    FILE* ptr = fopen("numbers_q1.txt", "r");

    int ar[n];
    for( int i = 0; i < n; i++ )
        fscanf(ptr, "%d", &ar[i]);
    fclose(ptr);

    int largest = ar[0], secondLargest = ar[0];
    int smallest = ar[0], secondSmallest;

    for( int i = 0; i < n; i++ ){
        if( ar[i] > largest ){
            secondLargest = largest;
            largest = ar[i];
        }
        else if( ar[i] > secondLargest && ar[i] != largest )
            secondLargest = ar[i];
        
        if( ar[i] < smallest ){
            secondSmallest = smallest;
            smallest = ar[i];
        }
        else if( ar[i] < secondSmallest && ar[i] != smallest )
            secondSmallest = ar[i];
    }
    printf("Second Smallest: %d\nSecond Largest: %d\n", secondSmallest, secondLargest);
    return 0;
}