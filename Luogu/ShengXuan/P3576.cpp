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
const int maxn = 1e6 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], tot;
inline void add(int x, int y) { E[++tot].next = head[x], head[x] = tot, E[tot].to = y; }
int n, m, k, w[maxn], deg[maxn], maxx;
long long res;
long long l[maxn], r[maxn];
void dfs(int u, int fa)
{
	if(l[u] > maxx) return;
    if (deg[u] == 1)
    {
        int ll = std::lower_bound(w + 1, w + 1 + m, l[u]) - w;
        int rr = std::upper_bound(w + 1, w + 1 + m, r[u]) - w;
        if (ll < rr) res += 1ll * (rr - ll) * k;
        return;
    }
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        int d = max(1, (deg[v] - 1));
        l[v] = l[u] * d, r[v] = r[u] * d + d - 1, dfs(v, u);
    }
}
int main()
{
    read(n), read(m), read(k);
    for (int i = 1; i <= m; ++i) read(w[i]);
    std::sort(w + 1, w + 1 + m);
    maxx = w[m];
    int s, t;
    read(s), read(t), add(s, t), add(t, s), deg[s]++, deg[t]++;
    for (int i = 2, u, v; i < n; ++i) read(u), read(v), add(u, v), add(v, u), deg[u]++, deg[v]++;
    int d = max(1, deg[s] - 1);
    l[s] = 1ll * k * d, r[s] = 1ll * k * d + d - 1;
    d = max(1, deg[t] - 1), l[t] = 1ll * k * d, r[t] = 1ll * k * d + d - 1;
    dfs(s, t), dfs(t, s);
    printf("%lld\n", res);
    return 0;
}
