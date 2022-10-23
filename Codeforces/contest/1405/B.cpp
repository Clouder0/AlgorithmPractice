#include <cstdio>
const int maxn = 3e5 + 100;
int T,n;
int a[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        long long sum = 0,res = 0;
        for(int i = n;i;--i)
        {
            if(a[i] < 0) sum -= a[i];
            else 
            {
                if(a[i] >= sum) res += a[i] - sum,sum = 0;
                else sum -= a[i];
            }
        }
        printf("%lld\n",res);
    }
}