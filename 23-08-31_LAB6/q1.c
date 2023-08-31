#include <stdio.h>

struct Item {
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
};

void insertionSort(struct Item arr[], int n) {
    for (int i = 1; i < n; i++) {
        struct Item key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].profit_weight_ratio < key.profit_weight_ratio) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void fractionalKnapsack(struct Item items[], int n, float capacity) {
    insertionSort(items, n);
    
    float total_profit = 0;
    float current_capacity = capacity;

    printf("Item No\tProfit\tWeight\tAmount to be taken\n");
    for (int i = 0; i < n; i++) {
        if (items[i].item_weight <= current_capacity) {
            printf("%d\t%.2f\t%.2f\t1.000000\n", items[i].item_id, items[i].item_profit, items[i].item_weight);
            total_profit += items[i].item_profit;
            current_capacity -= items[i].item_weight;
        }
        else if (current_capacity > 0.0) {
            float fraction = current_capacity / items[i].item_weight;
            printf("%d\t%.2f\t%.2f\t%.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);
            total_profit += items[i].item_profit * fraction;
            current_capacity = 0.0;
        } else {
            printf("%d\t%.2f\t%.2f\t0.000000\n", items[i].item_id, items[i].item_profit, items[i].item_weight);
        }
    }

    printf("Maximum profit: %.6f\n", total_profit);
}

int main() {
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct Item items[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        items[i].item_id = i + 1;
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    float capacity;
    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    fractionalKnapsack(items, n, capacity);

    return 0;
}
