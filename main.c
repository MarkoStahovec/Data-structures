#include <stdio.h>
#define MAX 1300000

char s[MAX];
int p[100000], n;

int main()
{
    int i = 2, j, k;
    scanf("%d", &k);
    for (; n < k; i++)
    {
        if (!s[i])
            p[n++] = i;
        for (j = i; j < MAX; j=i+j)
            s[j] = 1;
    }

    printf("%d\n", p[k-1]);
    return 0;
}