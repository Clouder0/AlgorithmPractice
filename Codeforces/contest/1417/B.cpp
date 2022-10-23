#include <cstdio>
const int maxn = 1e5 + 100;
int T,n,k,a[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&k);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        if(k & 1)
        {
            int left = k / 2;
            for (int i = 1; i <= n; ++i) if(a[i] <= left) printf("0 ");
            else printf("1 ");
        }
        else
        {
            int mid = k / 2,last = 1;
            for (int i = 1; i <= n; ++i)
                if (a[i] < mid) printf("0 ");
                else if (a[i] > mid) printf("1 ");
                else printf("%d ", last ^= 1);
        }
        puts("");
    }
    return 0;
}