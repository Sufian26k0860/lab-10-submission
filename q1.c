#include <stdio.h>

int main()
{
    FILE *fp;
    int n, q, no, st;
    float p, total = 0;
    char name[21];

    fp = fopen("items.txt", "wb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 1, "Rice", 250.0, 40);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 2, "Sugar", 160.0, 25);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 3, "Milk", 220.0, 30);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 4, "CookingOil", 560.0, 12);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 5, "Tea", 450.0, 18);
    fclose(fp);

    fp = fopen("items.txt", "rb+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while (1) {
        printf("Item no: ");
        scanf("%d", &n);
        if (n == 0)
            break;
        if (n < 1 || n > 5) {
            printf("Invalid item\n");
            continue;
        }
        printf("Quantity: ");
        scanf("%d", &q);

        fseek(fp, (n - 1) * 42, SEEK_SET);
        fscanf(fp, "%d %s %f %d", &no, name, &p, &st);

        if (q <= st) {
            printf("%s %d x %.2f = %.2f\n", name, q, p, q * p);
            total += q * p;
            st -= q;
            fseek(fp, (n - 1) * 42, SEEK_SET);
            fprintf(fp, "%-4d %-20s %9.2f %5d\n", no, name, p, st);
        } else {
            printf("Only %d %s in stock\n", st, name);
        }
    }

    printf("Total bill: %.2f\n", total);
    fclose(fp);
    return 0;
}
