#include <cstdio>
#include <algorithm>
#include <ctype.h>
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
const int maxn = 6e5 + 100;
struct node
{
    int to, next;
} E[maxn];
int head[maxn];
inline void add(const int &x,const int &y)
{
	static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int n, to[maxn * 10][2], sum[maxn * 10], cnt;
int v[maxn], root[maxn], siz[maxn], son[maxn], bin[maxn * 10], top;
bool w[maxn * 10];
inline int newnode() { return top ? bin[top--] : ++cnt; }
inline void del(int x) { to[x][0] = to[x][1] = sum[x] = w[x] = 0, bin[++top] = x; }
void pushup(int u)
{
    if (to[u][0] && to[u][1])
    {
        w[u] = w[to[u][0]] ^ w[to[u][1]];
        sum[u] = ((sum[to[u][0]] ^ sum[to[u][1]]) << 1) | w[to[u][1]];
    }
    else if (to[u][0]) w[u] = w[to[u][0]], sum[u] = sum[to[u][0]] << 1;
    else w[u] = w[to[u][1]], sum[u] = (sum[to[u][1]] << 1) | w[to[u][1]];
}
void ins(int u, int t, int h)
{
    if (h >= 23) return (void)(w[u] ^= 1);
    if (!to[u][t & 1]) to[u][t & 1] = newnode();
    ins(to[u][t & 1], t >> 1, h + 1), pushup(u);
}
void addall(int u)
{
    if (to[u][1]) addall(to[u][1]);
    std::swap(to[u][0], to[u][1]), pushup(u);
}
void merge(int& x, int y)
{
    if (!x || !y) return (void)(x += y);
    merge(to[x][0], to[y][0]), merge(to[x][1], to[y][1]), w[x] ^= w[y], sum[x] ^= sum[y], del(y);
}
long long ANS;
void pre(int u)
{
	siz[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        pre(v), siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}
void dfs(int u)
{
    if (son[u]) dfs(son[u]), merge(root[u], root[son[u]]);
    for (int p = head[u]; p; p = E[p].next)
    {
		int v = E[p].to;
		if(v == son[u]) continue;
        dfs(v), merge(root[u], root[v]);
    }
    addall(root[u]), ins(root[u], v[u], 0), ANS += sum[root[u]];
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(v[i]);
    for (int i = 2, x; i <= n; ++i) read(x), add(x, i);
	for (int i = 1; i <= n; ++i) root[i] = newnode();
    pre(1), dfs(1), printf("%lld\n", ANS);
    return 0;
}