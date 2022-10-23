#include <algorithm>
#include <cstdio>
#include <cctype>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
	#ifdef DEBUG
	return getchar();
	#endif
	static char buf[bufSize], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
	static char c;
	static int flag;
	flag = 1, r = 0;
	for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
	for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
	return r *= flag;
}
const int maxn = 3e5 + 100;
struct node
{
    int to, next, val;
} E[maxn << 1];
int head[maxn], tot;
inline void add(int x, int y, int z) { E[++tot].next = head[x], head[x] = tot, E[tot].to = y, E[tot].val = z; }
int n, s;
int dis[maxn], pre[maxn];
void dfs(int u, int fa)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dis[v] = dis[u] + E[p].val, pre[v] = u, dfs(v, u);
    }
}
int ondia[maxn], dia[maxn], cnt;
int maxdis[maxn], vis[maxn], bel[maxn], q[maxn], qt, qh;
int main()
{
    read(n), read(s);
    for (int i = 1, a, b, c; i < n; ++i) read(a), read(b), read(c), add(a, b, c), add(b, a, c);
    dfs(1, 0);
    int from = 1, to = 1;
    for (int i = 1; i <= n; ++i) if (dis[from] < dis[i]) from = i;
    dis[from] = 0, dfs(from, 0);
    for (int i = 1; i <= n; ++i) if (dis[to] < dis[i]) to = i;
    while (from != to) dia[++cnt] = to, to = pre[to];
    dia[++cnt] = from;
    reverse(dia + 1, dia + 1 + cnt);
    for (int i = 1; i <= cnt; ++i) ondia[dia[i]] = 1, q[++qt] = dia[i], bel[dia[i]] = dia[i];
    qh = 1;
    while (qt >= qh)
    {
        int u = q[qh++];
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (ondia[v] || vis[v]) continue;
            vis[v] = 1, maxdis[v] = maxdis[u] + E[p].val, bel[v] = bel[u];
            q[++qt] = v;
        }
    }
    for (int i = 1; i <= n; ++i) if (!ondia[i]) maxdis[bel[i]] = max(maxdis[bel[i]], maxdis[i]);
    qh = 1, qt = 0;
    int r = 0;
    int res = 1 << 30;
    for (int l = 1; l <= cnt; ++l)
    {
        while (r < cnt && dis[dia[r + 1]] - dis[dia[l]] <= s)
        {
            ++r;
            while (qt >= qh && maxdis[dia[q[qt]]] <= maxdis[dia[r]]) --qt;
            q[++qt] = r;
        }
        while (qt >= qh && q[qh] < l) ++qh;
        int left = dis[dia[l]], right = dis[dia[cnt]] - dis[dia[r]];
        int now = max(left, right);
        if (qt >= qh) now = max(now, maxdis[dia[q[qh]]]);
        res = min(res, now);
    }
    printf("%d\n", res);
    return 0;
}