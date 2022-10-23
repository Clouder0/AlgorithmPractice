#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
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
const int mod = 80112002;
const int maxn = 10000,maxm = 5e5 + 100;
struct node
{
    int to,next;
}E[maxm];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int n, m, f[maxn], g[maxn], q[maxn], qt, qh, in[maxn], out[maxn];
signed main()
{
    read(n), read(m);
    for (int i = 1, a, b; i <= m; ++i) read(a), read(b), add(a, b), out[a]++,in[b]++;
    qh = 1;
    for (int i = 1; i <= n; ++i) if (!in[i]) q[++qt] = i, f[i] = 1;
    while (qt >= qh)
    {
        int u = q[qh++];
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            f[v] = (f[v] + f[u]) % mod;
            if(--in[v] == 0) q[++qt] = v;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) if(!out[i]) ans = (ans + f[i]) % mod;
    printf("%d\n",ans);
    return 0;
}