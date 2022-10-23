#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 5e5 + 100;
struct node
{
	int to, next;
}E[maxn << 1];
int head[maxn], tot;
inline void add(int x, int y){ E[++tot].next = head[x], head[x] = tot, E[tot].to = y; }
int n, m, d, w[maxn], f[maxn][21], g[maxn][21], iskey[maxn];
const int inf = 1 << 29;
void dfs(int u, int fa)
{
	if(iskey[u]) f[u][0] = g[u][0] = w[u];
	for(int i = 1;i <= d; ++i) f[u][i] = w[u];
	f[u][d + 1] = g[u][d + 1] = inf;
	for(int p = head[u]; p; p = E[p].next)
	{
		int v = E[p].to;
		if(v == fa) continue;
		dfs(v, u);
		for(int i = d; i >= 0; --i) f[u][i] = min(f[v][i + 1] + g[u][i + 1],f[u][i] + g[v][i]);
		for(int i = d; i >= 0; --i) f[u][i] = min(f[u][i + 1], f[u][i]);
		g[u][0] = f[u][0];
		for(int i = 1; i <= d; ++i) g[u][i] += g[v][i - 1];
		for(int i = 1; i <= d; ++i) g[u][i] = min(g[u][i - 1], g[u][i]);
	}

}
int main()
{
	scanf("%d %d", &n, &d);
	for(int i = 1;i <= n;++i) scanf("%d", w + i);
	scanf("%d", &m);
	for(int i = 1, x; i <= m; ++i) scanf("%d", &x), iskey[x] = 1;
	for(int i = 1, u, v; i < n; ++i) scanf("%d %d", &u, &v), add(u, v), add(v, u);
	dfs(1, 0);
	printf("%d\n", g[1][0]);
	return 0;
}
