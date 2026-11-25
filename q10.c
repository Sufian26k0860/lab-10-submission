#include <stdio.h>
#include <string.h>

int countRepeat(char s[], int i)
{
    if (s[i + 1] != s[i])
        return 1;
    return 1 + countRepeat(s, i + 1);
}

void compress(char s[], int i, char out[], int j)
{
    if (s[i] == '\0')
    {
        out[j] = '\0';
        return;
    }
    int c = countRepeat(s, i);
    out[j] = s[i];
    out[j + 1] = c + '0';
    compress(s, i + c, out, j + 2);
}

void expand(char in[], int i, char out[], int j)
{
    if (in[i] == '\0')
    {
        out[j] = '\0';
        return;
    }
    int c = in[i + 1] - '0';
    for (int k = 0; k < c; k++)
        out[j + k] = in[i];
    expand(in, i + 2, out, j + c);
}

int main()
{
    char s[100], cmp[200], exp[100];
    printf("Enter string: ");
    scanf("%s", s);
    compress(s, 0, cmp, 0);
    expand(cmp, 0, exp, 0);
    printf("Original: %s\n", s);
    printf("Compressed: %s\n", cmp);
    printf("Expanded: %s\n", exp);
    printf("Match: %s\n", strcmp(s, exp) == 0 ? "Yes" : "No");
    return 0;
}
