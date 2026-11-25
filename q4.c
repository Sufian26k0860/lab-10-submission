#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp;
    int r, no, nt, i;
    char st, name[21], g[21];
    float rate;
    char guests[10][21];
    int rooms[10];

    fp = fopen("hotel.txt", "wb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    for (r = 101; r <= 110; r++)
        fprintf(fp, "%3d %c %-20s %2d %8.2f\n", r, 'F', "-", 0, 8000.0);
    fclose(fp);

    fp = fopen("hotel.txt", "rb+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while (1) {
        printf("Check-in room (0 to stop): ");
        scanf("%d", &r);
        if (r == 0)
            break;
        if (r < 101 || r > 110) {
            printf("Invalid room\n");
            continue;
        }
        printf("Name: ");
        scanf("%20s", g);
        printf("Nights: ");
        scanf("%d", &nt);

        fseek(fp, (r - 101) * 39, SEEK_SET);
        fscanf(fp, "%d %c %s %d %f", &no, &st, name, &i, &rate);
        if (st == 'F') {
            fseek(fp, (r - 101) * 39, SEEK_SET);
            fprintf(fp, "%3d %c %-20s %2d %8.2f\n", r, 'B', g, nt, rate);
            printf("Room %d booked\n", r);
        } else {
            printf("Room already booked\n");
        }
    }

    rewind(fp);
    for (i = 0; i < 10; i++)
        fscanf(fp, "%d %c %s %d %f", &rooms[i], &st, guests[i], &nt, &rate);

    printf("Search name: ");
    scanf("%20s", g);
    for (i = 0; i < 10; i++) {
        if (strcmp(guests[i], g) == 0) {
            printf("%s is in room %d\n", g, rooms[i]);
            break;
        }
    }
    if (i == 10)
        printf("%s not found\n", g);

    printf("Check-out room: ");
    scanf("%d", &r);
    if (r >= 101 && r <= 110) {
        fseek(fp, (r - 101) * 39, SEEK_SET);
        fscanf(fp, "%d %c %s %d %f", &no, &st, name, &nt, &rate);
        if (st == 'B') {
            printf("Bill: %d x %.2f = %.2f\n", nt, rate, nt * rate);
            fseek(fp, (r - 101) * 39, SEEK_SET);
            fprintf(fp, "%3d %c %-20s %2d %8.2f\n", r, 'F', "-", 0, rate);
        } else {
            printf("Room is not booked\n");
        }
    } else {
        printf("Invalid room\n");
    }

    fclose(fp);
    return 0;
}
