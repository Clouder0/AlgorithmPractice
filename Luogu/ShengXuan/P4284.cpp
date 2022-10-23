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
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
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
    double w;
}E[maxn << 1];
int head[maxn];
inline void add(const int &x,const int &y,const double &w)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,E[tot].w = w,head[x] = tot;
    E[++tot].next = head[y],E[tot].to = x,E[tot].w = w,head[y] = tot;
}
int n;
double f[maxn],q[maxn],g[maxn];
void dfs(int u,int fa)
{
    f[u] = 1.0 - q[u];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v, u), f[u] *= f[v] + (1.0 - f[v]) * (1.0 - E[p].w);
    }
}
void dfs2(int u,int fa)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        double t = g[u] / (f[v] + (1.0 - f[v]) * (1.0 - E[p].w));
        g[v] = f[v] * (t + (1.0 - t) * (1.0 - E[p].w)), dfs2(v, u);
    }
}
int main()
{
    read(n);
    for (int i = 1, a, b, p; i < n; ++i) read(a), read(b), read(p), add(a, b, p / 100.0);
    for (int i = 1, x; i <= n; ++i) read(x), q[i] = x / 100.0;
    dfs(1, 0), g[1] = f[1], dfs2(1, 0);
    double ans = 0;
    for (int i = 1; i <= n; ++i) ans += 1.0 - g[i];
    printf("%.6f",ans);
    return 0;
}