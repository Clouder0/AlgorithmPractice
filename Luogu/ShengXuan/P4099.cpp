#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 1100;
int T, n;
struct node
{
    int to, next, val;
} E[maxn << 1];
int head[maxn], tot;
inline void addE(int x, int y, int z) { E[++tot].next = head[x], head[x] = tot, E[tot].to = y, E[tot].val = z; }
const int mod = 1e9 + 7;
inline int add(int x, int y) { int res = x + y; return res >= mod ? res - mod : res; }
inline int mul(int x, int y) { return 1ll * x * y % mod; }
int C[maxn][maxn];
int size[maxn], f[maxn][maxn], g[maxn];
void dfs(int u, int fa)
{
    size[u] = 1, f[u][1] = 1;
    for(int p = head[u]; p; p = E[p].next)
	{
		int v = E[p].to;
        if (v == fa) continue;
        dfs(v, u);
        for (int i = 1; i <= size[u]; ++i) g[i] = 0;
        if (E[p].val)
        {
			for(int i = size[u]; i; --i) 
				for(int k = 0; k <= size[v]; ++k)
					g[i + k] = add(g[i + k],
						mul(f[v][k],
						mul(f[u][i],
						mul(C[i + k - 1][k],
						C[size[u] + size[v] - i - k][size[v] - k]))));
		}
		else
		{
			for(int i = size[u]; i; --i) 
				for(int k = 0; k <= size[v]; ++k)
                    g[i + k] = add(g[i + k],
                        mul(add(f[v][size[v]], mod - f[v][k]),
						mul(f[u][i],
						mul(C[i + k - 1][k],
						C[size[u] + size[v] - i - k][size[v] - k]))));
        }
		size[u] += size[v];
		for(int i = 1;i<=size[u];++i) f[u][i] = g[i];
	}
    for (int i = 1; i <= size[u]; ++i) f[u][i] = add(f[u][i], f[u][i - 1]);
}
int main()
{
    scanf("%d", &T);
    C[0][0] = 1;
    for (int i = 1; i <= 1000; ++i)
    {
        C[i][0] = 1;
        for (int j = 1; j <= 1000; ++j) C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
    }
    while(T--)
	{
        memset(f, 0, sizeof(f));
        memset(head, 0, sizeof(head));
        tot = 0;
        scanf("%d", &n);
        for (int i = 1, u, v; i < n; ++i)
        {
            char opt[3];
            scanf("%d %s %d", &u, opt, &v);
            ++u, ++v;
            if (opt[0] == '<') addE(u, v, 0), addE(v, u, 1);
            else addE(u, v, 1), addE(v, u, 0);
        }
        dfs(1, 0);
        printf("%d\n", f[1][n]);
    }
	return 0;
}

