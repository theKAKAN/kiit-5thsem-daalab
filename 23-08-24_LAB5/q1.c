#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int id;
    char name[50];
    int age;
    int height;
    int weight;
};

void swap(struct person** arr, int i, int j) {
    struct person* temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void minHeapify(struct person** arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left]->age < arr[smallest]->age)
        smallest = left;

    if (right < n && arr[right]->age < arr[smallest]->age)
        smallest = right;

    if (smallest != i) {
        swap(arr, i, smallest);
        minHeapify(arr, n, smallest);
    }
}

void createMinHeap(struct person** arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);
}

void maxHeapify(struct person** arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left]->weight > arr[largest]->weight)
        largest = left;

    if (right < n && arr[right]->weight > arr[largest]->weight)
        largest = right;

    if (largest != i) {
        swap(arr, i, largest);
        maxHeapify(arr, n, largest);
    }
}

void createMaxHeap(struct person** arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

void displayWeightOfYoungest(struct person** arr, int n) {
    if (n == 0) {
        printf("No data available.\n");
        return;
    }
    printf("Weight of the youngest person: %d\n", arr[0]->weight);
}

void insertPerson(struct person** arr, int* n) {
    struct person* p = (struct person*)malloc(sizeof(struct person));
    printf("Enter Id Name Age Height Weight: ");
    scanf("%d %s %d %d %d", &p->id, p->name, &p->age, &p->height, &p->weight);

    (*n)++;
    arr = (struct person**)realloc(arr, (*n) * sizeof(struct person*));
    arr[*n - 1] = p;

    createMinHeap(arr, *n);
}

void deleteOldestPerson(struct person** arr, int* n) {
    if (*n == 0) {
        printf("No data available.\n");
        return;
    }
    free(arr[0]);

    arr[0] = arr[*n - 1];
    (*n)--;

    createMinHeap(arr, *n);
}

void display( struct person **array, int n ){
    printf("\nID\tName\tAge\tHeight\tWeight\n");
    for( int i = 0; i < n; i++ ){
        printf("%d\t%s\t%d\t%d\t%d\n",
                    array[i]->id,
                    array[i]->name,
                    array[i]->age,
                    array[i]->height,
                    array[i]->weight
                );
    }
}

int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct person** arr = (struct person**)malloc(n * sizeof(struct person*));

    int option;
    do {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the youngest person\n");
        printf("7. Exit\n");
        printf("8. Display all\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Reading from file.");
                FILE *inputFile = fopen("input.txt", "r");
                int i = 0;
                while( i < n ){
                    arr[i] = (struct person*)malloc(sizeof(struct person));
                    fscanf(inputFile, "%d %s %d %d %d", 
                                &arr[i]->id, 
                                arr[i]->name,
                                &arr[i]->age,
                                &arr[i]->height,
                                &arr[i]->weight
                        );
                    printf("Hello");
                    i++;
                }
                printf("Read %d inputs", i);
                fclose(inputFile);
                break;
            case 2:
                createMinHeap(arr, n);
                break;
            case 3:
                createMaxHeap(arr, n);
                break;
            case 4:
                displayWeightOfYoungest(arr, n);
                break;
            case 5:
                insertPerson(arr, &n);
                break;
            case 6:
                deleteOldestPerson(arr, &n);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            case 8:
                display( arr, n );
                break;
            default:
                printf("Invalid option! Please enter a valid option.\n");
        }
    } while (option != 7);

    // Free allocated memory before exiting
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}