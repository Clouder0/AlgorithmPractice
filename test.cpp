#include <bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define debug printf("Now is Line : %d\n", __LINE__)
#define file(a)                    \
	freopen(#a ".in", "r", stdin); \
	freopen(#a ".out", "w", stdout)
#define int long long
#define inf 123456789000000000
#define mod 1000000007
il int read()
{
	re int x = 0, f = 1;
	re char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = x * 10 + c - 48, c = getchar();
	return x * f;
}
#define maxn 250005
struct edge
{
	int v, w, next;
} e[maxn << 1];
int n, m, head[maxn], cnt, is[maxn], mi[maxn], dfn[maxn], col, t;
int size[maxn], fa[maxn], top[maxn], son[maxn], dep[maxn], s[maxn];
vector<int> v[maxn];
il void add(int u, int v, int w)
{
	e[++cnt] = (edge){v, w, head[u]};
	head[u] = cnt;
}
il bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
il void dfs1(int u, int fr)
{
	size[u] = 1, fa[u] = fr, dep[u] = dep[fr] + 1;
	for (re int i = head[u]; i; i = e[i].next)
	{
		int v = e[i].v;
		if (v == fr)
			continue;
		mi[v] = min(mi[u], e[i].w);
		dfs1(v, u), size[u] += size[v];
		if (size[son[u]] < size[v])
			son[u] = v;
	}
}
il void dfs2(int u, int fr)
{
	top[u] = fr, dfn[u] = ++col;
	if (!son[u])
		return;
	dfs2(son[u], fr);
	for (re int i = head[u]; i; i = e[i].next)
	{
		int v = e[i].v;
		if (v != fa[u] && v != son[u])
			dfs2(v, v);
	}
}
il int lca(int a, int b)
{
	while (top[a] != top[b])
		dep[top[a]] > dep[top[b]] ? a = fa[top[a]] : b = fa[top[b]];
	return dep[a] < dep[b] ? a : b;
}
il void push(int x)
{
	if (t == 1)
	{
		s[++t] = x;
		return;
	}
	int l = lca(x, s[t]);
	if (l == s[t])
		return;
	while (t > 1 && dfn[s[t - 1]] >= dfn[l])
		v[s[t - 1]].push_back(s[t]), --t;
	if (s[t] != l)
		v[l].push_back(s[t]), s[t] = l;
	s[++t] = x;
}
il int dp(int u)
{
	if (v[u].size() == 0)
		return mi[u];
	int temp = 0;
	for (re int i = 0; i < v[u].size(); ++i)
		temp += dp(v[u][i]);
	v[u].clear();
	return min(mi[u], temp);
}
signed main()
{
	n = read();
	for (re int i = 1; i < n; ++i)
	{
		int u = read(), v = read(), w = read();
		add(u, v, w), add(v, u, w);
	}
	mi[1] = inf, dfs1(1, 0), dfs2(1, 1);
	int T = read();
	while (T--)
	{
		m = read();
		for (re int i = 1; i <= m; ++i)
			is[i] = read();
		sort(is + 1, is + m + 1, cmp);
		s[t = 1] = 1;
		for (re int i = 1; i <= m; ++i)
			push(is[i]);
		while (t > 0)
			v[s[t - 1]].push_back(s[t]), --t;
		printf("%lld\n", dp(1));
	}
	return 0;
}