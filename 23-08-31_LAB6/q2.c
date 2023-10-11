#include <stdio.h>
#include <stdlib.h>

struct SYMBOL {
    char alphabet;
    int frequency;
    struct SYMBOL *left, *right;
};

struct MinPriorityQueue {
    int size;
    struct SYMBOL **array;
};

void swap(struct SYMBOL **a, struct SYMBOL **b) {
    struct SYMBOL *temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct MinPriorityQueue *minHeap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != index) {
        swap(&minHeap->array[index], &minHeap->array[smallest]);
        minHeapify(minHeap, smallest);
    }
}

struct SYMBOL *extractMin(struct MinPriorityQueue *minHeap) {
    struct SYMBOL *minSymbol = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return minSymbol;
}

void insert(struct MinPriorityQueue *minHeap, struct SYMBOL *symbol) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && symbol->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = symbol;
}

struct MinPriorityQueue *buildMinHeap(struct SYMBOL *symbols[], int n) {
    struct MinPriorityQueue *minHeap = (struct MinPriorityQueue *)malloc(sizeof(struct MinPriorityQueue));
    minHeap->size = n;
    minHeap->array = symbols;

    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(minHeap, i);
    }

    return minHeap;
}

struct SYMBOL *constructHuffmanTree(struct SYMBOL *symbols[], int n) {
    struct MinPriorityQueue *minHeap = buildMinHeap(symbols, n);

    while (minHeap->size > 1) {
        struct SYMBOL *left = extractMin(minHeap);
        struct SYMBOL *right = extractMin(minHeap);

        struct SYMBOL *combined = (struct SYMBOL *)malloc(sizeof(struct SYMBOL));
        combined->alphabet = '*';
        combined->frequency = left->frequency + right->frequency;
        combined->left = left;
        combined->right = right;

        insert(minHeap, combined);
    }

    return minHeap->array[0];
}

void inOrderTraversal(struct SYMBOL *root) {
    if (root) {
        inOrderTraversal(root->left);
        if (root->alphabet != '*') {
            printf("%c ", root->alphabet);
        }
        inOrderTraversal(root->right);
    }
}

int main() {
    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    struct SYMBOL *symbols[n];
    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++) {
        // Create a symbol
        symbols[i] = (struct SYMBOL *)malloc(sizeof(struct SYMBOL));
        symbols[i]->left = NULL;
        symbols[i]->right = NULL;
        // Scan all the alphabets
        scanf(" %c", &symbols[i]->alphabet);
    }
    printf("Enter its frequencies: ");
    for(int i = 0; i < n; i++){
        scanf("%d", &symbols[i]->frequency);
    }

    struct SYMBOL *huffmanRoot = constructHuffmanTree(symbols, n);

    printf("In-order traversal of the tree (Huffman): ");
    inOrderTraversal(huffmanRoot);

    return 0;
}