#include <iostream>
#include <memory.h>
#include <cstdio>
using namespace std;
const int N = 100005;
template <typename T>
inline void read(T &r)
{
	static char c;
	r = 0;
	for (c = getchar(); c > '9' || c < '0'; c = getchar());
	for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
int n, dis[N], d, ans;
struct node
{
	int to, next;
} E[N << 1];
int head[N];
int tot;
void addedge(int u, int v)
{
	E[++tot] = (node){v, head[u]}, head[u] = tot;
	E[++tot] = (node){u, head[v]}, head[v] = tot;
}

void dfs(int u, int f)
{
	if (dis[u] > d)
		ans++;
	for (int p = head[u]; p; p = E[p].next)
	{
		int v = E[p].to;
		if (v == f)
			continue;
		dis[v] = dis[u] + 1;
		dfs(v, u);
	}
}
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		tot = 0;
		memset(head, 0, sizeof(head));
		read(n);
		read(d);
		int u, v;
		for (int i = 1; i < n; i++)
		{
			read(u);
			read(v);
			addedge(u, v);
		}
		ans = 0;
		dfs(0, 0);
		printf("%d\n", ans);
	}
	return 0;
}