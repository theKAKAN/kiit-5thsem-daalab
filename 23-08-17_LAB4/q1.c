#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SEC_TO_NS 1000000000
#define MAX_READ 400

void merge(int elements[], int low, int middle, int high, int* comparisions) {
    int n1 = middle - low + 1;
    int n2 = high - middle;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = elements[low + i];
    for (int j = 0; j < n2; j++)
        R[j] = elements[middle + 1 + j];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        (*comparisions)++;
        if (L[i] <= R[j]) {
            elements[k++] = L[i++];
        } else {
            elements[k++] = R[j++];
        }
    }

    while (i < n1) {
        elements[k++] = L[i++];
    }

    while (j < n2) {
        elements[k++] = R[j++];
    }
}

void mergeSort(int elements[], int low, int high, int* comparisions) {
    if (low < high) {
        int middle = (low + high)/2;
        mergeSort(elements, low, middle, comparisions);
        mergeSort(elements, middle + 1, high, comparisions);
        merge(elements, low, middle, high, comparisions);
    }
}

int main() {
    FILE *inputFile, *outputFile;
    int elements[MAX_READ]; 
    int choice, size, comparisons = 0;
    clock_t start, end;
    double cpu_time_used;

    while (1) {
        printf("MAIN MENU (Merge Sort)\n");
        printf("\t1. Ascending Data\n");
        printf("\t2. Descending Data\n");
        printf("\t3. Random Data\n");
        printf("\t4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) {
            break;
        }

        switch (choice) {
            case 1:
                inputFile = fopen("q1_inAsc.dat", "r");
                outputFile = fopen("q1_outAsc.dat", "w");
                break;
            case 2:
                inputFile = fopen("q1_inDesc.dat", "r");
                outputFile = fopen("q1_outDesc.dat", "w");
                break;
            case 3:
                inputFile = fopen("q1_inRand.dat", "r");
                outputFile = fopen("q1_outRand.dat", "w");
                break;
            default:
                printf("Invalid choice entered\n");
                continue;
        }

        if (inputFile == NULL || outputFile == NULL) {
            printf("cant open the file\n");
            return 1;
        }


        // Print the file
        printf("Before sorting: ");
        size = 0;
        while( size < MAX_READ && fscanf(inputFile, "%d", &elements[size]) == 1 ) {
            // Print the element
            printf("%d ", elements[size]);
            // Increase size after printing
            size++;
        }
        fclose(inputFile);

        comparisons = 0;
        start = clock();
        mergeSort(elements, 0, size - 1, &comparisons);
        end = clock();
        cpu_time_used = ((double) (end - start))*SEC_TO_NS / CLOCKS_PER_SEC;

        // Print to output too
        printf("\nAfter sorting: ");
        for (int i = 0; i < size; i++) {
            fprintf(outputFile, "%d ", elements[i]);
            printf("%d ", elements[i]);
        }
        fclose(outputFile);

        printf("\nNumber of comparisons: %d\n", comparisons);
        printf("Execution time: %.2f nanoseconds\n", cpu_time_used);
    }

    return 0;
}