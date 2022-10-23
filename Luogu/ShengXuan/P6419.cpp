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
const int maxn = 5e5 + 100;
struct node
{
    int to, next, val;
} E[maxn << 1];
int head[maxn];
inline void add(const int& x, const int& y, const int& val)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,E[tot].val = val,head[x] = tot;
}
int n, k, point[maxn], size[maxn], iskey[maxn];
long long f[maxn], maxx[maxn], secx[maxn], g[maxn], ANS[maxn];
void dfs(int u, int fa)
{
    size[u] = iskey[u];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs(v, u); 
        if(!size[v]) continue;
        size[u] += size[v];
        if (size[v]) f[u] += f[v] + (E[p].val << 1);
        int len = maxx[v] + E[p].val;
        if (len >= maxx[u]) secx[u] = maxx[u], maxx[u] = len; // not strictly greater
        else if (len > secx[u]) secx[u] = len;
    }
}
void dfs2(int u, int fa)
{
    ANS[u] = g[u] - maxx[u];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        g[v] = f[v];
        if(k - size[v]) 
        {
            g[v] += g[u] + (E[p].val << 1);
            if (size[v]) g[v] -= f[v] + (E[p].val << 1);
            if (maxx[u] > maxx[v] + E[p].val) secx[v] = std::max(secx[u] + E[p].val, maxx[v]), maxx[v] = maxx[u] + E[p].val;
            else
            {
                int len = secx[u] + E[p].val;
                if (len >= maxx[v]) secx[v] = maxx[v], maxx[v] = len;
                else if (len > secx[v]) secx[v] = len;
            }
        }
       dfs2(v, u);
    }
}
int main()
{
    read(n),read(k);
    for (int i = 1, a, b, c; i < n; ++i) read(a), read(b), read(c), add(a, b, c), add(b, a, c);
    for (int i = 1; i <= k; ++i) read(point[i]), iskey[point[i]] = 1;
    dfs(1, 0), g[1] = f[1], dfs2(1, 0);
    for (int i = 1; i <= n; ++i) printf("%lld\n", ANS[i]);
    //puts("");
    //for (int i = 1; i <= n; ++i) printf("%d %d %d %d %d\n", i, f[i], g[i], maxx[i], secx[i]);
    return 0;
}