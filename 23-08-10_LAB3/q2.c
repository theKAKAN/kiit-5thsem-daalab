#include <stdio.h>
#include <stdlib.h>

#define MAX_READ 400

// Function to perform insertion sort
int insertionSort(int arr[], int n) {
    int comparisons = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            comparisons++;
        }
        
        arr[j + 1] = key;
    }
    return comparisons;
}

void displayFileContent(char *filename) {
    FILE *destFile = fopen(filename, "r");
    if (destFile == NULL) {
        printf("Error opening destination file for reading: %s\n", filename);
        return;
    }

    char binaryNum[100];
    while (fgets( binaryNum, sizeof(binaryNum), destFile) != NULL) {
        printf("%s", binaryNum);
    }

    fclose(destFile);
}

int main() {
    int choice;
    printf("Menu:\n");
    printf("\t1. Ascending Order\n");
    printf("\t2. Descending Order\n");
    printf("\t3. Random Order\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    char *inputFilename, *outputFilename;
    switch (choice) {
        case 1:
            inputFilename = "q2_inAsc.dat";
            outputFilename = "q2_outInAsc.dat";
            break;
        case 2:
            inputFilename = "q2_inDesc.dat";
            outputFilename = "q2_outInDesc.dat";
            break;
        case 3:
            inputFilename = "q2_inRand.dat";
            outputFilename = "q2_outInRand.dat";
            break;
        default:
            printf("Invalid choice\n");
            return 1;
    }
    
    FILE *inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        printf("Error opening input file %s\n", inputFilename);
        return 1;
    }
    
    int n = 0, arr[MAX_READ];

    int num;

    while(fscanf(inputFile, "%d", &num) == 1 && n < MAX_READ ){
        arr[n] = num;
        n++;
    }

    fclose(inputFile);
    
    int comparisons = insertionSort(arr, n);
    
    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("Error creating output file %s\n", outputFilename);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "%d ", arr[i]);
    }
    fprintf(outputFile, "\nNumber of comparisons: %d", comparisons);
    fclose(outputFile);
    
    // Read
    displayFileContent(outputFilename);

    return 0;
}
