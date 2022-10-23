#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 1e5 + 100;
struct node { int to, next, val; } E[maxn << 1];
int head[maxn], tot;
inline void add(int x, int y, int z) { E[++tot].next = head[x], head[x] = tot, E[tot].to = y, E[tot].val = z; }
int n, d, k[maxn], f[maxn], last[maxn], g[maxn], vis[maxn], res;
bool rcmp(pair<int,int> a,pair<int,int> b) { return a.first > b.first; }
vector<pair<int,int> > V[maxn];
void dfs(int u, int fa)
{
	for(int p = head[u], v; p; p = E[p].next)
	{
		if((v = E[p].to) == fa) continue;
		dfs(v, u), V[u].push_back(make_pair(f[v] + E[p].val, v));
	}
	sort(V[u].begin(), V[u].end(), rcmp);
	for(int i = 0; i < (int)V[u].size() && i < k[u] - 1; ++i) f[u] += V[u][i].first;
}
void dfs2(int u, int fa, int faval)
{
	if(u != d && k[u] == 1) return;
	g[u] = faval;
	int up = k[u] - 2 + !fa;
	for(int i = 0; i < (int)V[u].size() && i < up; ++i) g[u] += V[u][i].first, vis[V[u][i].second] = 1;
	res = std::max(res, g[u]);
	int t = 0;
	if(V[u].size() > up) t = V[u][up].first;
	for(int p = head[u], v; p; p = E[p].next)
	{
		if((v = E[p].to) == fa) continue;
		if(vis[v]) dfs2(v, u, g[u] - f[v] - E[p].val + t + E[p].val);
		else dfs2(v, u, g[u] + E[p].val);
	}
}
int main()
{
	scanf("%d %d", &n, &d);
	for(int i = 1, a, b, c; i < n; ++i) scanf("%d %d %d", &a, &b, &c), add(a, b, c), add(b, a, c);
	for(int i = 1; i <= n; ++i) scanf("%d", k + i);
	dfs(d, 0), dfs2(d, 0, 0);
	printf("%d\n",res);
	return 0;
}
