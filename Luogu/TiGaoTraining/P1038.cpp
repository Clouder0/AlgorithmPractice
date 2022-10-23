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
const int maxn = 1e5;
struct node
{
    int to,next,val;
}E[maxn];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,E[tot].val = val,head[x] = tot;
}
int n, p, bel[maxn], C[maxn], U[maxn], vis[maxn];
int q[maxn], qt, qh;
int main()
{
    read(n), read(p);
    for (int i = 1; i <= n; ++i) read(C[i]), read(U[i]);
    qh = 1;
    for (int i = 1; i <= n; ++i) if (C[i] > 0) bel[i] = 1, q[++qt] = i;
    for (int i = 1, a, b, c; i <= p; ++i)
    {
        read(a), read(b), read(c);
        if(bel[a] == 1) add(a,b,c);
        else if(bel[b] == 1) add(b,a,c);
        else add(a, b, c), add(b, a, c);
    }
    while(qt >= qh)
    {
        int u = q[qh++];
        if(vis[u]) continue;
        vis[u] = 1;
        if(bel[u] != 1) C[u] -= U[u];
        bool flag = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (vis[v]) continue;
            if (C[u] > 0) C[v] += E[p].val * C[u];
            q[++qt] = v;
            flag = 0;
        }
        if(flag) bel[u] = 2;
    }
    bool flag = 0;
    for (int i = 1; i <= n; ++i) if(bel[i] == 2 && C[i] > 0) printf("%d %d\n",i,C[i]),flag = 1;
    if(!flag) puts("NULL");
    return 0;
}