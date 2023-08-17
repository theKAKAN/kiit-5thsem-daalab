#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int partition(int elements[], int low, int high, int *comparisions);
void swap(int *a, int *b);
void quickSort(int elements[], int low, int high, int *comparisions);


int main() {
    int choice;
    FILE *inputFile, *outputFile;
    int elements[500]; 
    int size;
    int comparisons = 0;

    while (1) {
        printf("MAIN MENU (QUICK SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) {
            break;
        }

        switch (choice) {
            case 1:
                inputFile = fopen("inputAscending.txt", "r");
                outputFile = fopen("outQuickAsce.txt", "w");
                break;
            case 2:
                inputFile = fopen("inputDescending.txt", "r");
                outputFile = fopen("outQuickDesc.txt", "w");
                break;
            case 3:
                inputFile = fopen("inputRandom.txt", "r");
                outputFile = fopen("outQuickRand.txt", "w");
                break;
            default:
                printf("invalid choice entered\n");
                continue;
        }

        if (inputFile == NULL || outputFile == NULL) {
            printf("cant open file\n");
            return 1;
        }

        size = 0;
        while (fscanf(inputFile, "%d", &elements[size]) == 1) {
            size++;
        }

        fclose(inputFile);

        comparisons = 0;
        quickSort(elements, 0, size - 1, &comparisons);

        fprintf(outputFile, "Sorted elements:\n");
        for (int i = 0; i < size; i++) {
            fprintf(outputFile, "%d ", elements[i]);
        }
        fprintf(outputFile, "\nNumber of comparisons: %d\n", comparisons);

        fclose(outputFile);

        printf("Sorting completed.\n");
    }

    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int elements[], int low, int high, int *comparisions) {
    int pivot = elements[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        (*comparisions)++;
        if (elements[j] <= pivot) {
            i++;
            swap(&elements[i], &elements[j]);
        }
    }
    swap(&elements[i + 1], &elements[high]);
    return i + 1;
}

void quickSort(int elements[], int low, int high, int *comparisions) {
    if (low < high) {
        int pi = partition(elements, low, high, comparisions);
        quickSort(elements, low, pi - 1, comparisions);
        quickSort(elements, pi + 1, high, comparisions);
    }
}

