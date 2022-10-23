#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 1100;
int T, n;
struct node
{
	int to, next, val;
}E[maxn << 1];
int head[maxn], tot;
inline void addE(int x, int y, int z){ E[++tot].next = head[x], head[x] = tot, E[tot].to = y, E[tot].val = z; }
const int mod = 1e9 + 7;
inline int add(int x, int y){ int res = x + y; return res >= mod ? res - mod : res; }
inline int mul(int x, int y){ return 1ll * x * y % mod; }
int C[maxn][maxn];
int size[maxn], f[maxn][maxn], g[maxn];
void dfs(int u, int fa)
{
	size[u] = 1,f[u][1] = 1;
	for(int p = head[u]; p; p = E[p].next)
	{
		int v = E[p].to;
		if(v == fa) continue;
		dfs(v,u);
        memset(g, 0, sizeof(g));
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
						mul(add(f[v][size[v]],mod - f[v][k]),
						mul(f[u][i],
						mul(C[i+k-1][k],
						C[size[u] + size[v] - i - k][size[v] - k]))));
		}
		size[u] += size[v];
        memcpy(f[u], g, sizeof(g));
    }
    for(int i = 1;i<=size[u];++i) f[u][i] = add(f[u][i],f[u][i-1]);
}
char s[100000];
int main()
{
	C[0][0] = 1;
	for(int i = 1;i <= 1000; ++i) 
	{
		C[i][0] = 1;
		for(int j = 1;j <= 1000; ++j) C[i][j] = add(C[i-1][j],C[i-1][j-1]);
	}
		scanf("%d %s",&n,s + 2);
		
		for(int i = 2;i<=n;++i)
		{
			if(s[i] == '<') addE(i/2,i,0);
			else addE(i/2,i,1);
		}
		dfs(1,0);
		printf("%d\n",f[1][n]);
	return 0;
}


