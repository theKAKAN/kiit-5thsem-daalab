#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void processPairs(FILE *src, FILE *dest) {
    int num1, num2;
    while (fscanf(src, "%d %d", &num1, &num2) == 2) {
        int result = gcd(num1, num2);
        fprintf(dest, "The GCD of %d and %d is %d\n", num1, num2, result);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <sourceFile> <destFile>\n", argv[0]);
        return 1;
    }

    FILE *sourceFile = fopen(argv[1], "r");
    if (sourceFile == NULL) {
        printf("Error opening source file: %s\n", argv[1]);
        return 1;
    }

    FILE *destFile = fopen(argv[2], "w");
    if (destFile == NULL) {
        printf("Error opening destination file: %s\n", argv[2]);
        fclose(sourceFile);
        return 1;
    }

    processPairs(sourceFile, destFile);

    // Close files
    fclose(sourceFile);
    fclose(destFile);

    // Read
    destFile = fopen(argv[2], "r");
    if (destFile == NULL) {
        printf("Error opening destination file for reading: %s\n", argv[2]);
        return 1;
    }

    char binaryNum[100];
    while (fgets( binaryNum, sizeof(binaryNum), destFile) != NULL) {
        printf("%s", binaryNum);
    }

    fclose(destFile);

    return 0;
}
