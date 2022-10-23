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
const int maxn = 1e6 + 100;
struct node
{
    int to,next;
}E[maxn << 1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int n, a[maxn], sum, size[maxn], ans[10], cnt,rt;
void dfs(int u, int fa)
{
    size[u] = a[u];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs(v, u), size[u] += size[v];
    }
    if (u != rt && size[u] == sum / 3) { ans[++cnt] = u, size[u] = 0; }
}
int main()
{
    read(n);
    for (int i = 1, x; i <= n; ++i) 
    {
        read(x), read(a[i]), sum += a[i];
        if (!x) rt = i;
        else add(x, i);
    }
    if (sum % 3) { puts("-1"); return 0; }
    dfs(rt, 0);
    if (cnt < 2) { puts("-1"); }
    else printf("%d %d\n", ans[1], ans[2]);
    return 0;
}