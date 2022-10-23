#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 110;
const int maxm = 21000;
int s,n,m;
int a[maxn][maxn];
int f[maxm];
int main()
{
    scanf("%d %d %d",&s,&n,&m);
    for (int i = 1; i <= s; ++i)
        for (int j = 1; j <= n; ++j) scanf("%d", a[j] + i);
    for (int i = 1; i <= n; ++i) std::sort(a[i] + 1, a[i] + 1 + s);
    memset(f, ~0x3f, sizeof(f));
    f[m] = 0;
    for (int i = 1; i <= n; ++i)
        for (int k = 0; k <= m; ++k)
            for (int j = 1; j <= s; ++j)
                if(k - 2 * a[i][j] > 0) 
                    f[k - 2 * a[i][j] - 1] = max(f[k - 2 * a[i][j] - 1], f[k] + i * j);
    int ans = 0;
    for (int i = 0; i <= m; ++i) ans = max(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}