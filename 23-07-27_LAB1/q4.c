#include <stdio.h>

void EXCHANGE( int *p1, int *p2 ){
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void ROTATE_RIGHT( int ar[], int n ){
    n = n-1;
    // 5 as input should mean the 5th element, not 6th( counted from 0 )
    int last = ar[n];
    for( int i = n; i > 0; i-- ){
        EXCHANGE( &ar[i], &ar[i-1] );
    }
    EXCHANGE( &ar[0], &last );
}

int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d integers now: ", n);
    for( int i = 0; i < n; i++ )
        scanf("%d", &arr[i]);
    
    int rot;
    printf("Where to rotate to: ");
    scanf("%d", &rot);

    
    printf("\nOriginal Array: ");
    for( int i = 0; i < n; i++ )
        printf("%d ", arr[i]);
    
    ROTATE_RIGHT( arr, rot );

    printf("\nModified Array: ");
    for( int i = 0; i < n; i++ )
        printf("%d ", arr[i]);
    
    printf("\n");
    return 0;
}