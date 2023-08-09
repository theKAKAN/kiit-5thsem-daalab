/*
Write a program to implement Binary Search to give the position of
leftmost appearance of the element in the array being searched. Display the number of
comparisons made while searching.
Input:
Enter size of array: 10
Enter elements of the array: 2 3 7 7 7 11 12 12 20 50
Enter the key to be searched: 7
Output:
7 found at index position 2
Number of comparisons: 3
*/

#include <stdio.h>

int leftmostBinarySearch(int arr[], int size, int target, int *comparisons) {
    int left = 0, right = size - 1;
    int position = -1;  // Initialize position to -1 (not found)

    while (left <= right) {
        int mid = left + (right - left) / 2;
        (*comparisons)++;

        if (arr[mid] == target) {
            position = mid;
            right = mid - 1;  // Continue searching to the left for the leftmost occurrence
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return position;
}

int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter elements: ");
    for( int i = 0; i < n; i++ )
        scanf("%d", &arr[i]);
    
    
    int target;
    printf("Enter target to search: ");
    scanf("%d", &target );
    
    printf("\n");

    int comparisons = 0;
    int position = leftmostBinarySearch(arr, n, target, &comparisons);

    if (position != -1) {
        printf("Element %d found at position %d\n", target, position);
    } else {
        printf("Element %d not found in the array\n", target);
    }

    printf("Number of comparisons made: %d\n", comparisons);

    return 0;
}
