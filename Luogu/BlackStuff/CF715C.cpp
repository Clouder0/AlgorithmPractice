#include <cstdio>
#include <algorithm>
#include <map>
#include <ctype.h>
using namespace std;
#define int long long
#define DEBUG
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
const int maxn = 1e5 + 100;
struct node
{
    int to, next, val;
} E[maxn << 1];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, head[x] = tot;
}
int n, m, inv[maxn],pw[maxn];
void exgcd(int a,int b,int &x,int &y)
{
    if (!b) return (void)(x = 1, y = 0);
    exgcd(b, a % b, y, x), y -= (a / b) * x;
}
inline int getinv(int x)
{
    int k1,k2;
    exgcd(x, m, k1, k2);
    return ((k1 % m) + m) % m;
}
int vis[maxn], treeSize, size[maxn], maxx[maxn], root, dep[maxn], ANS, dis[maxn];
void getroot(int u, int fa)
{
    maxx[u] = 0, size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa || vis[v]) continue;
        getroot(v, u), size[u] += size[v];
        maxx[u] = max(maxx[u], size[v]);
    }
    maxx[u] = max(maxx[u], treeSize - size[u]);
    if (maxx[u] < maxx[root]) root = u;
}
map<int,int> mp;
void debugoutput()
{
    for(int i = 0;i<5;++i) printf("debug:%d %d\n",i,mp[i]);
    puts("");
}
void update(int u, int fa, int val)
{
    size[u] = 1,dep[u] = dep[fa] + 1, mp[(m - dis[u]) % m] += val;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (vis[v] || v == fa) continue;
        dis[v] = (((1ll * dis[u] + 1ll * E[p].val * pw[dep[u]]) % m) + m) % m, update(v, u, val), size[u] += size[v];
    }
}
void getans(int u,int fa)
{
    map<int,int>::iterator it = mp.find((1ll * dis[u] * inv[dep[u]]) % m);
    if(it != mp.end()) ANS += it->second;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(vis[v] || v == fa) continue;
        dis[v] = (1ll * dis[u] * 10 + E[p].val) % m, getans(v, u);
    }
}
void solve(int u)
{
    maxx[root = 0] = 1 << 30, getroot(u, 0);
    vis[u = root] = 1, dep[u] = 0, dis[u] = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(vis[v]) continue;
        dis[v] = ((E[p].val) % m + m) % m, update(v, u, 1);
    }
    ANS += mp[0];
    mp[0]++;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(vis[v]) continue;
        update(v, u, -1);
        getans(v, u);
        update(v, u, 1);
    }
    mp.clear();
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(vis[v]) continue;
        treeSize = size[v], solve(v);
    }
}
signed main()
{
    read(n),read(m);
    for (int i = 1, a, b, c; i < n; ++i) read(a), read(b), read(c), ++a,++b,add(a, b, c), add(b, a, c);
    pw[0] = 1;
    for (int i = 1; i <= n; ++i) pw[i] = (pw[i - 1] * 10) % m;
    for (int i = 0; i <= n; ++i) inv[i] = getinv(pw[i]);
    treeSize = n, solve(1);
    printf("%lld\n", ANS);
    return 0;
}