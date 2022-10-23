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
const int maxn = 2e5 + 100;
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
int n, m, a[maxn], dep[maxn], size[maxn], in[maxn], out[maxn], ind, sum[maxn];
inline int lowbit(int x) { return x & -x; }
void ins(int x,int k) { for (; x <= n; x += lowbit(x)) sum[x] += k; }
int ask(int x)
{
    int res = 0;
    for (; x > 0; x -= lowbit(x)) res += sum[x];
    return res;
}
void dfs(int u,int fa)
{
    in[u] = ++ind, size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dep[v] = dep[u] + 1, dfs(v, u), size[u] += size[v];
    }
    out[u] = ind;
}

int main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dep[1] = 1, dfs(1, 0);
    for (int i = 1,x,y,opt; i <= m; ++i) 
    {
        read(opt);
        if(opt == 1) 
        {
            read(x), read(y);
            if (dep[x] & 1) ins(in[x], y), ins(out[x] + 1, -y);
            else ins(in[x], -y), ins(out[x] + 1, y);
        }
        else
        {
            read(x);
            if(dep[x] & 1) printf("%d\n",a[x] + ask(in[x]));
            else printf("%d\n",a[x] - ask(in[x]));
        }
    }
    return 0;
}