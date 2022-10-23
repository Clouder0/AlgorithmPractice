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
const int maxn = 110;
const int maxm = 1e5 + 100;
int n, S, T;
struct node
{
    int to,next,val;
}E[maxm];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,E[tot].val = val,head[x] = tot;
}
int dis[maxn],vis[maxn],q[maxm * 2],qt,qh;
int main()
{
    read(n),read(S),read(T);
    for (int i = 1,x,k; i <= n; ++i) 
    {
        read(k);
        if(!k) continue;
        read(x), add(i, x, 0);
        for (int j = 1; j < k; ++j) read(x), add(i, x, 1);
    }
    for (int i = 1; i <= n; ++i) dis[i] = 1 << 30;
    qh = qt = maxm, q[maxm] = S, dis[S] = 0;
    while (qt >= qh)
    {
        int u = q[qh++];
        if(vis[u]) continue;
        vis[u] = 1;
        if(u == T) break;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (E[p].val == 0) dis[v] = min(dis[v],dis[u]), q[--qh] = v;
            else dis[v] = min(dis[v],dis[u] + 1), q[++qt] = v;
        }
    }
    if(dis[T] >= (1 << 30)) puts("-1");
    else printf("%d\n",dis[T]);
    return 0;
}