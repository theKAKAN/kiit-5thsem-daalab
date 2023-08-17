#include <stdio.h>
#include <time.h>
#include <stdlib.h>
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
    int choice;
    FILE *inputFile, *outputFile;
    int elements[500]; 
    int size;
    int comparisons = 0;
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
                outputFile = fopen("outMergeAsce.txt", "w");
                break;
            case 2:
                inputFile = fopen("inDescending.txt", "r");
                outputFile = fopen("outMergeDesc.txt", "w");
                break;
            case 3:
                inputFile = fopen("inRandom.txt", "r");
                outputFile = fopen("outMergeRand.txt", "w");
                break;
            default:
                printf("invalid choice entered\n");
                continue;
        }

        if (inputFile == NULL || outputFile == NULL) {
            printf("cant open the file\n");
            return 1;
        }

        size = 0;
        while (fscanf(inputFile, "%d", &elements[size]) == 1) {
            size++;
        }

        fclose(inputFile);

        comparisons = 0;
        start = clock();
        mergeSort(elements, 0, size - 1, &comparisons);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        for (int i = 0; i < size; i++) {
            fprintf(outputFile, "%d ", elements[i]);
        }
        fclose(outputFile);

        printf("Sorting completed.\n");
        printf("Number of comparisons: %d\n", comparisons);
        printf("Execution time: %f seconds\n", cpu_time_used);
    }

    return 0;
}