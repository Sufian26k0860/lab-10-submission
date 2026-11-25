#include <stdio.h>

int main()
{
    FILE *fp;
    char cat[13], c1[13], c2[13];
    float amt, a1, a2, total = 0;
    int e;

    fp = fopen("expenses.txt", "rb");
    if (fp == NULL) {
        fp = fopen("expenses.txt", "wb");
        fprintf(fp, "%-12s %9.2f\n", "Food", 1200.0);
        fprintf(fp, "%-12s %9.2f\n", "Transport", 500.0);
        fprintf(fp, "%-12s %9.2f\n", "Books", 850.0);
        fprintf(fp, "%-12s %9.2f\n", "Mobile", 300.0);
    }
    fclose(fp);

    printf("Category: ");
    scanf("%12s", cat);
    printf("Amount: ");
    scanf("%f", &amt);

    fp = fopen("expenses.txt", "ab");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    fprintf(fp, "%-12s %9.2f\n", cat, amt);
    fclose(fp);

    fp = fopen("expenses.txt", "rb+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fseek(fp, -2 * 23, SEEK_END);
    fscanf(fp, "%s %f", c1, &a1);
    fscanf(fp, "%s %f", c2, &a2);
    printf("Latest two: %s %.2f, %s %.2f\n", c1, a1, c2, a2);

    printf("Entry to fix: ");
    scanf("%d", &e);
    printf("Correct amount: ");
    scanf("%f", &amt);
    fseek(fp, (e - 1) * 23, SEEK_SET);
    if (fscanf(fp, "%s", cat) == 1) {
        fseek(fp, (e - 1) * 23, SEEK_SET);
        fprintf(fp, "%-12s %9.2f\n", cat, amt);
    } else {
        printf("Invalid entry\n");
    }

    rewind(fp);
    while (fscanf(fp, "%s %f", cat, &amt) == 2) {
        printf("%s %.2f\n", cat, amt);
        total += amt;
    }
    printf("Total: %.2f\n", total);

    fclose(fp);
    return 0;
}
