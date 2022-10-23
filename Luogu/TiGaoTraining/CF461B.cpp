#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 1e5 + 100;
const int mod = 1e9 + 7;
struct node
{
    int to, next;
} E[maxn];
int head[maxn], tot;
inline void addE(int x, int y) { E[++tot].next = head[x], head[x] = tot, E[tot].to = y; }
int n, fa[maxn], w[maxn], f[maxn][2];
inline int add(int x, int y)
{
    int res = x + y;
    return res >= mod ? res - mod : res;
}
inline int mul(int x, int y) { return 1ll * x * y % mod; }
void dfs(int u)
{
    f[u][w[u]] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        dfs(v);
        f[u][1] = add(mul(f[u][0], f[v][1]), mul(f[u][1], add(f[v][0], f[v][1])));
        f[u][0] = mul(f[u][0], add(f[v][0], f[v][1]));
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) scanf("%d", fa + i), ++fa[i], addE(fa[i], i);
    for (int i = 1; i <= n; ++i) scanf("%d", w + i);
    dfs(1);
    printf("%d\n", f[1][1]);
    return 0;
}
