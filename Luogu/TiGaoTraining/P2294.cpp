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
const int maxn = 1e4,maxm = 1e5;
int T,n,m;
struct node
{
    int to,next,val;
}E[maxm];
int head[maxn],tot;
inline void add(const int &x,const int &y,const int &val)
{
    E[++tot].next = head[x],E[tot].to = y,E[tot].val = val,head[x] = tot;
}
int vis[maxn],inq[maxn],dis[maxn],q[maxn],qt,qh;
int main()
{
    read(T);
    while(T--)
    {
        read(n),read(m);
        tot = 0;
        for (int i = 1; i <= n + 1; ++i) head[i] = 0;
        for (int i = 1, a, b, c; i <= m; ++i) read(a), read(b), read(c), add(b + 1, a, c), add(a, b + 1, -c);
        for (int i = 2; i <= n + 1; ++i) dis[i] = 1 << 30;
        for (int i = 1; i <= n + 1; ++i) inq[i] = vis[i] = 0;
        qt = qh = 1, q[1] = 1, dis[1] = 0;
        while(qt >= qh)
        {
            int u = q[qh++];
            inq[u] = 0;
            if(vis[u] > n + 10) goto fail;
            for (int p = head[u]; p; p = E[p].next)
            {
                int v = E[p].to;
                if (dis[v] > dis[u] + E[p].val) 
                {
                    dis[v] = dis[u] + E[p].val, vis[v] = vis[u] + 1;
                    if (!inq[v]) q[++qt] = v,inq[v] = 1;
                }
            }
        }
        puts("true");
        continue;
    fail:
        puts("false");
    }
    return 0;
}