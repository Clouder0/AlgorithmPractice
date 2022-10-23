#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 3e5 + 100;
int T,n,pos[maxn],a[maxn],mindis[maxn],minn[maxn],vis[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for (int i = 1; i <= n; ++i) pos[i] = 0, mindis[i] = 0, minn[i] = 1 << 30,vis[i] = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", a + i),vis[a[i]] = 1;
        for (int i = 1; i <= n; ++i) mindis[a[i]] = max(mindis[a[i]], i - pos[a[i]]), pos[a[i]] = i;
        for (int i = 1; i <= n; ++i) mindis[i] = max(mindis[i], n - pos[i] + 1);
        for (int i = 1; i <= n; ++i) if (vis[i] && mindis[i] <= n) minn[mindis[i]] = min(minn[mindis[i]], i);
        for (int i = 2; i <= n; ++i) minn[i] = min(minn[i], minn[i - 1]);
        for (int i = 1; i <= n; ++i) if (minn[i] == 1 << 30) printf("-1 "); else printf("%d ", minn[i]);
        puts("");
    }
    return 0;
}