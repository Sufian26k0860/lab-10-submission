#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp;
    char name[11], hot[11];
    float t, max;
    int i, n;

    fp = fopen("temperature.txt", "wb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    for (i = 0; i < 5; i++) {
        printf("City %d name: ", i + 1);
        scanf("%10s", name);
        printf("Temperature: ");
        scanf("%f", &t);
        fprintf(fp, "%-10s %5.1f\n", name, t);
    }
    fclose(fp);

    fp = fopen("temperature.txt", "rb+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    printf("City number: ");
    scanf("%d", &n);
    if (n >= 1 && n <= 5) {
        fseek(fp, (n - 1) * 17, SEEK_SET);
        fscanf(fp, "%s %f", name, &t);
        printf("%s %.1f\n", name, t);
    } else {
        printf("Invalid city number\n");
    }

    printf("City number to correct: ");
    scanf("%d", &n);
    printf("New temperature: ");
    scanf("%f", &t);
    if (n >= 1 && n <= 5) {
        fseek(fp, (n - 1) * 17, SEEK_SET);
        fscanf(fp, "%s", name);
        fseek(fp, (n - 1) * 17, SEEK_SET);
        fprintf(fp, "%-10s %5.1f\n", name, t);
        printf("%s updated to %.1f\n", name, t);
    } else {
        printf("Invalid city number\n");
    }

    rewind(fp);
    for (i = 0; i < 5; i++) {
        fscanf(fp, "%s %f", name, &t);
        if (i == 0 || t > max) {
            max = t;
            strcpy(hot, name);
        }
    }
    printf("Hottest city: %s (%.1f)\n", hot, max);

    fclose(fp);
    return 0;
}
