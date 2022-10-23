#include <cstdio>
int T,n;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d", &n);
        double last = n, now = 0;
        for (int i = 2; i <= n; ++i)
        {
            now = last + n * 1.0 / i;
            last = now;
        }
        printf("%.2f\n", last);
    }
    return 0;
}