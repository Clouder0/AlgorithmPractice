#include <cstdio>
#include <algorithm>
#include <ctype.h>
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
const int maxn = 5e5 + 100;
struct node
{
    int to,next;
}E[maxn];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int n, m;
unsigned S;
inline unsigned get() {
	S ^= S << 13;
	S ^= S >> 17;
	S ^= S << 5;
	return S; 
}
int top[maxn],id[maxn],ind,lg[maxn], fa[maxn][21], dep[maxn], son[maxn], maxdep[maxn],up[maxn],down[maxn];
void dfs(int u)
{
    for (int i = 1; i <= 20; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        dep[v] = maxdep[v] = dep[u] + 1, dfs(v);
        if (maxdep[v] > maxdep[son[u]]) son[u] = v;
        maxdep[u] = max(maxdep[u], maxdep[v]);
    }
}
void dfs2(int u,int p)
{
    id[u] = ++ind;
    down[ind] = u, up[ind] = p;
    if (son[u]) top[son[u]] = top[u], dfs2(son[u], fa[p][0]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == son[u]) continue;
        top[v] = v, dfs2(v, v);
    }
}
int ask(int x,int k)
{
    if(!k) return x;
    x = fa[x][lg[k]],k -= (1 << lg[k]);
    k -= dep[x] - dep[top[x]], x = top[x];
    if (k >= 0) return up[id[x] + k];
    else return down[id[x] - k];
}
int main()
{
    read(n), read(m), read(S);
    for (int i = 1; i <= n; ++i) read(fa[i][0]);
    int root = 0;
    for (int i = 1; i <= n; ++i) if(fa[i][0]) add(fa[i][0],i); else root = i;
    for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;
    dep[root] = 1, dfs(root), top[root] = root, dfs2(root, root);
    long long ans = 0;
    int last = 0;
    for (int i = 1; i <= m; ++i) 
    {
        int x = ((get() ^ last) % n) + 1;
        int k = ((get() ^ last) % dep[x]);
        ans ^= 1ll * i * (last = ask(x,k));
    }
    printf("%lld\n",ans);
    return 0;
}