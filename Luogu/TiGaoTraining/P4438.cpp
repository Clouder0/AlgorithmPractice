#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 100;
int n, ls[maxn], rs[maxn], a[maxn], b[maxn], c[maxn], dfn[maxn],s[maxn],top,ind;
inline int newnode(){return top ? s[top--] : ++ind;}
inline void delnode(int x) { s[++top] = x; }
long long f[100][100][100];
void dfs(int u,int maxx,int maxy)
{
    dfn[u] = newnode();
    if(u > n)
    {
        for (int i = 0; i <= maxx; ++i) for (int j = 0; j <= maxy; ++j) f[dfn[u]][i][j] = 1ll * c[u] * (a[u] + i) * (b[u] + j);
        return;
    }
    dfs(ls[u], maxx + 1, maxy), dfs(rs[u], maxx, maxy + 1);
    for (int i = 0; i <= maxx; ++i)
        for (int j = 0; j <= maxy; ++j)
            f[dfn[u]][i][j] = min(f[dfn[ls[u]]][i + 1][j] + f[dfn[rs[u]]][i][j], f[dfn[ls[u]]][i][j] + f[dfn[rs[u]]][i][j + 1]);
    delnode(dfn[ls[u]]),delnode(dfn[rs[u]]);
}
int main()
{
    scanf("%d",&n);
    for (int i = 1; i < n; ++i) scanf("%d %d", ls + i, rs + i),ls[i] = (ls[i] > 0 ? ls[i] : n - ls[i]),rs[i] = (rs[i] > 0 ? rs[i] : n - rs[i]);
    for (int i = 1; i <= n; ++i) scanf("%d %d %d", a + n + i, b + n + i, c + n + i);
    dfs(1, 0, 0);
    printf("%lld\n",f[dfn[1]][0][0]);
    return 0;
}