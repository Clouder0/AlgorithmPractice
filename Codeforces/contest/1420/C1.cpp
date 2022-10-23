#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 3e5 + 100;
int T,n,q;
long long a[maxn],f[maxn][2];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&q);
        for (int i = 1; i <= n; ++i) scanf("%lld",a + i);
        f[0][0] = -(1ll<<60);
        for (int i = 1; i <= n; ++i) 
        {
            f[i][0] = max(f[i - 1][0], f[i - 1][1] + a[i]);
            f[i][1] = max(f[i - 1][1], f[i - 1][0] - a[i]);
        }
        printf("%lld\n",max(f[n][0],f[n][1]));
    }
    return 0;
}