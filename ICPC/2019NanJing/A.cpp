#include <cstdio>
int T,n;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        printf("%d\n", (n + 1) / 2  + 1);
    }
    return 0;
}