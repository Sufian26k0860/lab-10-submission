#include <stdio.h>

int main()
{
    FILE *fp;
    int r, no, att, l;
    char name[16];
    float per;

    fp = fopen("attendance.txt", "wb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    fprintf(fp, "%-3d %-15s %3d\n", 1, "Ayesha", 18);
    fprintf(fp, "%-3d %-15s %3d\n", 2, "Bilal", 14);
    fprintf(fp, "%-3d %-15s %3d\n", 3, "Hamza", 20);
    fprintf(fp, "%-3d %-15s %3d\n", 4, "Sana", 12);
    fprintf(fp, "%-3d %-15s %3d\n", 5, "Zainab", 16);
    fclose(fp);

    fp = fopen("attendance.txt", "rb+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    printf("Roll number: ");
    scanf("%d", &r);
    if (r >= 1 && r <= 5) {
        fseek(fp, (r - 1) * 24, SEEK_SET);
        fscanf(fp, "%d %s %d", &no, name, &att);
        per = att * 100.0 / 20;
        printf("%s: %d / 20 (%.1f%%)", name, att, per);
        if (per < 75)
            printf(" Short attendance");
        printf("\n");
    } else {
        printf("Invalid roll number\n");
    }

    printf("Roll number for leave: ");
    scanf("%d", &r);
    printf("Lectures: ");
    scanf("%d", &l);
    if (r >= 1 && r <= 5) {
        fseek(fp, (r - 1) * 24, SEEK_SET);
        fscanf(fp, "%d %s %d", &no, name, &att);
        att += l;
        if (att > 20)
            att = 20;
        fseek(fp, (r - 1) * 24, SEEK_SET);
        fprintf(fp, "%-3d %-15s %3d\n", no, name, att);
        printf("%s: now %d / 20 (%.1f%%)\n", name, att, att * 100.0 / 20);
    } else {
        printf("Invalid roll number\n");
    }

    fseek(fp, -24, SEEK_END);
    fscanf(fp, "%d %s %d", &no, name, &att);
    printf("Last record: %d %s %d\n", no, name, att);

    fclose(fp);
    return 0;
}
