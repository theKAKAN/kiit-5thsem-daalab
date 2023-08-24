#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

struct min_heap {
    struct person *arr;
    int size;
    int capacity;
};

void swap(struct person *a, struct person *b) {
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct min_heap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->arr[left].age < heap->arr[smallest].age)
        smallest = left;

    if (right < heap->size && heap->arr[right].age < heap->arr[smallest].age)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->arr[idx], &heap->arr[smallest]);
        minHeapify(heap, smallest);
    }
}

struct min_heap *createMinHeap(int capacity) {
    struct min_heap *heap = (struct min_heap *)malloc(sizeof(struct min_heap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->arr = (struct person *)malloc(capacity * sizeof(struct person));
    return heap;
}

void insert(struct min_heap *heap, struct person p) {
    if (heap->size == heap->capacity) {
        printf("Heap is full. Cannot insert.\n");
        return;
    }

    heap->size++;
    int i = heap->size - 1;
    heap->arr[i] = p;

    while (i != 0 && heap->arr[(i - 1) / 2].age > heap->arr[i].age) {
        swap(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void buildMinHeap(struct min_heap *heap) {
    for (int i = (heap->size - 1) / 2; i >= 0; i--) {
        minHeapify(heap, i);
    }
}

void printHeap(struct min_heap *heap) {
    printf("Min Heap based on age:\n");
    for (int i = 0; i < heap->size; i++) {
        printf("Name: %s, Age: %d\n", heap->arr[i].name, heap->arr[i].age);
    }
}

int main() {
    struct min_heap *heap = createMinHeap(10);

    struct person p1 = {1, "Alice", 25, 165, 55};
    struct person p2 = {2, "Bob", 30, 175, 70};
    struct person p3 = {3, "Charlie", 22, 180, 80};

    insert(heap, p1);
    insert(heap, p2);
    insert(heap, p3);

    buildMinHeap(heap);

    printHeap(heap);

    free(heap->arr);
    free(heap);

    return 0;
}
