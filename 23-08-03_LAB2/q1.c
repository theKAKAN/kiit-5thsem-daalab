#include <stdio.h>
#include <stdlib.h>

void dToB(FILE *sourceFile, FILE *destFile, int n) {
    if (n <= 0) {
        return;
    }

    int decimalNum;
    fscanf(sourceFile, "%d", &decimalNum);

    // Keep the number
    int temp = decimalNum;
    // Convert decimal to binary
    // Use {0} to set everything to 0 by default
    int binaryNum[32] = {0};
    int i = 0;
    while (decimalNum > 0) {
        binaryNum[i] = decimalNum % 2;
        decimalNum /= 2;
        i++;
    }

    // Write binary to destination file
    fprintf(destFile, "The binary equivalent of %d is ", temp);
    for (int j = 31; j >= 0; j--) {
        fprintf(destFile, "%d", binaryNum[j]);
    }
    fprintf(destFile, "\n");

    // Call for next number
    dToB(sourceFile, destFile, n - 1);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    FILE *sourceFile = fopen(argv[2], "r");
    if (sourceFile == NULL) {
        printf("Error opening source file: %s\n", argv[2]);
        return 1;
    }

    FILE *destFile = fopen(argv[3], "w");
    if (destFile == NULL) {
        printf("Error opening destination file: %s\n", argv[3]);
        fclose(sourceFile);
        return 1;
    }

    dToB(sourceFile, destFile, n);

    // Close files
    fclose(sourceFile);
    fclose(destFile);

    // Read
    destFile = fopen(argv[3], "r");
    if (destFile == NULL) {
        printf("Error opening destination file for reading: %s\n", argv[3]);
        return 1;
    }

    char binaryNum[100];
    while (fgets( binaryNum, sizeof(binaryNum), destFile) != NULL) {
        printf("%s", binaryNum);
    }

    fclose(destFile);
    
    return 0;
}
