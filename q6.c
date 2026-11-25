#include <stdio.h>

void grow(int h[], int n)
{
    if (n == 0)
        return;
    h[n - 1] += (int)(h[n - 1] * 0.10);
    grow(h, n - 1);
}

int tallest(int h[], int n)
{
    int p;
    if (n == 0)
        return -1;
    p = tallest(h, n - 1);
    if (p == -1 || h[n - 1] > h[p])
        return n - 1;
    return p;
}

int search(int h[], int n, int t)
{
    if (n == 0)
        return -1;
    if (h[n - 1] == t)
        return n - 1;
    return search(h, n - 1, t);
}

int main()
{
    int ids[6] = {101, 102, 103, 104, 105, 106};
    int heights[6] = {45, 120, 78, 200, 95, 150};
    int i, t, p;

    grow(heights, 6);
    printf("New heights: ");
    for (i = 0; i < 6; i++)
        printf("%d ", heights[i]);
    printf("\n");

    p = tallest(heights, 6);
    printf("Tallest: tower %d (%d m)\n", ids[p], heights[p]);

    printf("Height to search: ");
    scanf("%d", &t);
    p = search(heights, 6, t);
    if (p == -1)
        printf("No tower is %d m\n", t);
    else
        printf("Tower %d is %d m\n", ids[p], heights[p]);

    return 0;
}
