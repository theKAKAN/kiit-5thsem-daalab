#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_READ 400

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




void displayFileContent(char *filename) {
    FILE *destFile = fopen(filename, "r");
    if (destFile == NULL) {
        printf("Error opening destination file for reading: %s\n", filename);
        return;
    }

    char line[100];
    while (fgets( line, sizeof(line), destFile) != NULL) {
        printf("%s", line);
    }

    fclose(destFile);
}

int main() {
    FILE *inputFile, *outputFile;
    int elements[MAX_READ]; 
    int choice, size, comparisons = 0;

    while (1) {
        printf("MAIN MENU (QUICK SORT)\n");
        printf("\t1. Ascending Data\n");
        printf("\t2. Descending Data\n");
        printf("\t3. Random Data\n");
        printf("\t4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) {
            break;
        }
        // Read input from the common input files
        switch (choice) {
            case 1:
                inputFile = fopen("q1_inAsc.dat", "r");
                outputFile = fopen("q2_outAsc.dat", "w");
                break;
            case 2:
                inputFile = fopen("q1_inDesc.dat", "r");
                outputFile = fopen("q2_outDesc.dat", "w");
                break;
            case 3:
                inputFile = fopen("q1_inRand.dat", "r");
                outputFile = fopen("q2_outRand.dat", "w");
                break;
            default:
                printf("invalid choice entered\n");
                continue;
        }

        if (inputFile == NULL || outputFile == NULL) {
            printf("cant open file\n");
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
        quickSort(elements, 0, size - 1, &comparisons);

        // Print to terminal too
        printf("\nAfter sorting: ");
        fprintf(outputFile, "\nAfter sorting: ");
        for (int i = 0; i < size; i++) {
            fprintf(outputFile, "%d ", elements[i]);
            printf("%d ", elements[i]);
        }
        fprintf(outputFile, "\nNumber of comparisons: %d\n", comparisons);
        printf("\nNumber of comparisons: %d\n", comparisons);

        fclose(outputFile);

        
        printf("\n");
    }

    return 0;
}