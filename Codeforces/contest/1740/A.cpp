#include <cstdio>
int T, n;
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        if (n == 2) puts("7");
        else if (n == 3) puts("5");
        else puts("3");
    }
    return 0;
}