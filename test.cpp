#include <bits/stdc++.h>
#define y1 y1_
#define index index_
#define pipe pipe_
#define next next_
#define endl '\n'
#define rgi register int
#define ll long long
#define Pi acos(-1.0)
#define lowbit(x) ((x & (-x)))
#define pb push_back
#define mk make_pair
#define pii pair<int, int>
#define fst first
#define scd second
using namespace std;
inline int read()
{
	int f = 1, x = 0;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch))
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
const int MAXN = 1e5 + 5;
struct EDGE
{
	int next, to;
} edge[MAXN << 1];
int head[MAXN], tot;
inline void add(int u, int v)
{
	edge[++tot].next = head[u];
	edge[tot].to = v;
	head[u] = tot;
}
int n, c[MAXN];
bool done[MAXN];
/*找重心*/
int f[MAXN], sz[MAXN], Size, root;
void getroot(int u, int fa)
{
	sz[u] = 1;
	f[u] = 0;
	for (rgi i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (v == fa || done[v])
			continue;
		getroot(v, u);
		sz[u] += sz[v];
		f[u] = max(f[u], sz[v]);
	}
	f[u] = max(f[u], Size - sz[u]);
	root = f[u] < f[root] ? u : root;
}
/*计算贡献*/
ll ans[MAXN], cnt[MAXN], col[MAXN], sum, num, S;
void dfs1(int u, int fa)
{
	sz[u] = 1;
	cnt[c[u]]++; /*根不一样了,sz必须要重搞*/
	for (rgi i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (v == fa || done[v])
			continue;
		dfs1(v, u);
		sz[u] += sz[v];
	}
	if (cnt[c[u]] == 1)
	{
		sum += sz[u];
		col[c[u]] += sz[u]; /*记录下每种颜色的贡献*/
	}
	cnt[c[u]]--;
}
void change(int u, int fa, int k)
{
	cnt[c[u]]++;
	for (rgi i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (v == fa || done[v])
			continue;
		change(v, u, k);
	}
	if (cnt[c[u]] == 1)
	{
		sum += sz[u] * k;
		col[c[u]] += sz[u] * k;
	}
	cnt[c[u]]--;
}
void dfs2(int u, int fa)
{
	cnt[c[u]]++;
	if (cnt[c[u]] == 1)
	{
		sum -= col[c[u]];
		num++;
	}
	ans[u] += sum + num * S;
	for (rgi i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (v == fa || done[v])
			continue;
		dfs2(v, u);
	}
	if (cnt[c[u]] == 1)
	{
		sum += col[c[u]];
		num--;
	}
	cnt[c[u]]--;
}
void clear(int u, int fa)
{
	cnt[c[u]] = col[c[u]] = 0;
	for (rgi i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (v == fa || done[v])
			continue;
		clear(v, u);
	}
}
void calc(int u)
{
	dfs1(u, 0);
	ans[u] += sum;
	for (rgi i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (done[v])
			continue;
		cnt[c[u]]++;
		sum -= sz[v];
		col[c[u]] -= sz[v];
		change(v, u, -1);
		cnt[c[u]]--;
		S = sz[u] - sz[v];
		dfs2(v, u);
		cnt[c[u]]++;
		sum += sz[v];
		col[c[u]] += sz[v];
		change(v, u, 1); /*改回去*/
		cnt[c[u]]--;
	}
	sum = 0;
	num = 0;
	clear(u, 0);
}
/*点分治*/
void work(int u)
{
	calc(u);
	done[u] = 1;
	for (rgi i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (done[v])
			continue;
		f[0] = Size = sz[v];
		root = 0;
		getroot(v, 0);
		work(root);
	}
}
int main()
{
	//	freopen("","r",stdin);
	//	freopen("","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0); /*syn加速*/
	n = read();
	for (rgi i = 1; i <= n; ++i)
		c[i] = read();
	for (rgi i = 1; i <= n - 1; ++i)
	{
		int u, v;
		u = read();
		v = read();
		add(u, v);
		add(v, u);
	}
	f[0] = Size = n;
	root = 0;
	getroot(1, 0);
	work(root);
	for (rgi i = 1; i <= n; ++i)
		cout << ans[i] << endl;
	return 0;
}
