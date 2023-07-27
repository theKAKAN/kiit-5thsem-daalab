#include <stdio.h>

int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    int arr[n], prefixArr[n];
    printf("Enter %d integers now: ", n);
    for( int i = 0; i < n; i++ )
        scanf("%d", &arr[i]);

    printf("Prefix output: ");
    for( int i = 0; i < n; i++ ){
        prefixArr[i] +=  i > 0 ? prefixArr[i-1] + arr[i] : arr[i];
        printf("%d ", prefixArr[i]);
    }
    printf("\n");
    
    return 0;
}