#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct person {
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

void swap(struct person *a, struct person *b);
void min_heapify(struct person *array, int n, int i);
void max_heapify(struct person *array, int n, int i);
void minheapbuild(struct person *array, int n);
void maxheapbuild(struct person *array, int n);
void youngest_wt(struct person *array);
void insert_in_heap(struct person *array, int *n, struct person newPerson) ;
void delete_old(struct person *array, int *n);
void display( struct person *array, int n );


int main() {
    int choice, n = 0;
    struct person *array = NULL;

    do {
        printf("\n Main Menu\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("8. Display all\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Read Data
                printf("Enter the number of students: ");
                scanf("%d", &n);
                array = (struct person *)malloc((n+1) * sizeof(struct person));

                /*for (int i = 0; i < n; i++) {
                    array[i].name = (char *)malloc(50 * sizeof(char));
                    printf("Enter data for student %d:\n", i + 1);
                    printf("ID: ");
                    scanf("%d", &array[i].id);
                    printf("Name: ");
                    scanf("%s", array[i].name);
                    printf("Age: ");
                    scanf("%d", &array[i].age);
                    printf("Height: ");
                    scanf("%d", &array[i].height);
                    printf("Weight: ");
                    scanf("%d", &array[i].weight);
                }*/
                FILE *inputFile = fopen("input.txt", "r");
                int i = 0;
                array[i].name = (char *)malloc(50 * sizeof(char));
                while( i < n ){
                    fscanf(inputFile, "%d %s %d %d %d", 
                                &array[i].id, 
                                array[i].name,
                                &array[i].age,
                                &array[i].height,
                                &array[i].weight
                        );
                    printf("Hello");
                    i++;
                    array[i].name = (char *)malloc(50 * sizeof(char));
                }
                printf("Read %d inputs", i);
                n = i;
                break;

            case 2: 
                minheapbuild(array, n);
                printf("Min-heap based on age created.\n");
                break;

            case 3: 
                maxheapbuild(array, n);
                printf("Max-heap based on weight created.\n");
                break;

            case 4: 
                if (n > 0)
                    youngest_wt(array);
                else
                    printf("data unavailable\n");
                break;

            case 5: 
                if (n < 1) {
                    printf("Please read data first.\n");
                    break;
                }
                struct person newPerson;
                newPerson.name = (char *)malloc(50 * sizeof(char));
                printf("Enter data for the new person:\n");
                printf("ID: ");
                scanf("%d", &newPerson.id);
                printf("Name: ");
                scanf("%s", newPerson.name);
                printf("Age: ");
                scanf("%d", &newPerson.age);
                printf("Height: ");
                scanf("%d", &newPerson.height);
                printf("Weight: ");
                scanf("%d", &newPerson.weight);
                insert_in_heap(array, &n, newPerson);
                printf("New person inserted into the Min-heap.\n");
                break;

            case 6: 
                if (n > 0) {
                    delete_old(array, &n);
                    printf("Oldest person deleted .\n");
                } else {
                    printf("data unavailable\n");
                }
                break;

            case 7: 
                free(array);// deallocating the dynamically allocated array of structures
                printf("Exiting program.\n");
                break;
            
            case 8: display(array, n); break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 7);

    return 0;
}

void swap(struct person *a, struct person *b) {
    struct person temp = *a;
    *a = *b;
    *b = temp;
}


void min_heapify(struct person *array, int n, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && array[l].age < array[smallest].age)
        smallest = l;

    if (r < n && array[r].age < array[smallest].age)
        smallest = r;

    if (smallest != i) {
        swap(&array[i], &array[smallest]);
        min_heapify(array, n, smallest);
    }
}

void max_heapify(struct person *array, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && array[l].weight > array[largest].weight)
        largest = l;

    if (r < n && array[r].weight > array[largest].weight)
        largest = r;

    if (largest != i) {
        swap(&array[i], &array[largest]);
        max_heapify(array, n, largest);
    }
}

void minheapbuild(struct person *array, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        min_heapify(array, n, i);
}

void maxheapbuild(struct person *array, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        max_heapify(array, n, i);
}

void youngest_wt(struct person *array) {
    printf("Weight of the youngest person: %d\n", array[0].weight);
}


void insert_in_heap(struct person *array, int *n, struct person newPerson) {
    (*n)++;
    int i = *n - 1;
    array[i] = newPerson;

    while (i > 0 && array[(i - 1) / 2].age > array[i].age) {
        swap(&array[i], &array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Delete the oldest person
void delete_old(struct person *array, int *n) {
    if (*n == 0)
        return;

    swap(&array[0], &array[*n - 1]);
    (*n)--;
    min_heapify(array, *n, 0);
}

void display( struct person *array, int n ){
    printf("\nID\tName\tAge\tHeight\tWeight\n");
    for( int i = 0; i < n; i++ ){
        printf("%d\t%s\t%d\t%d\t%d\n",
                    array[i].id,
                    array[i].name,
                    array[i].age,
                    array[i].height,
                    array[i].weight
                );
    }
}