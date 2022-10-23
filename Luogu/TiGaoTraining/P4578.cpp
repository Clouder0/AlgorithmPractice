#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define int long long
#define DEBUG
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
const int maxn = 1e6, maxm = 2e6;
int T, n, m, k;
struct node
{
    int to,next,val;
}E[maxm];
int head[maxn],tot;
inline void add(const int &x,const int &y,const int &val)
{
    E[++tot].next = head[x],E[tot].to = y,E[tot].val = val,head[x] = tot;
}
int dis[maxn], vis[maxn], q[maxn], inq[maxn],qt, qh,A[1100][1100],ex[1100][1100];
signed main()
{
    read(T);
    while(T--)
    {
        tot = 0;
        read(n), read(m), read(k);
        for (int i = 1; i <= n + m + 1; ++i) dis[i] = 1ll << 60, head[i] = 0, vis[i] = 0, inq[i] = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) ex[i][j] = 0;
        for (int i = 1, a, b, c; i <= k; ++i) 
        {
            read(a), read(b), read(c), add(a, b + n, c), add(b + n, a, -c);
            if(!ex[a][b]) ex[a][b] = 1,A[a][b] = c;
            else if(A[a][b] != c) {puts("No"); goto end;}
        }
        for (int i = 1; i <= n + m; ++i) add(n + m + 1, i, 0);
        dis[n + m + 1] = 0;
        qh = 1,q[qt = 1] = n + m + 1;
        while(qt >= qh)
        {
            int u = q[qh++];
            inq[u] = 0;
            if(vis[u] > n + m + 10) { puts("No"); goto end; }
            for (int p = head[u]; p; p = E[p].next)
            {
                int v = E[p].to;
                if(dis[v] > dis[u] + E[p].val)
                {
                    dis[v] = dis[u] + E[p].val;
                    vis[v] = vis[u] + 1;
                    if(!inq[v]) inq[v] = 1,q[++qt] = v;
                }
            }
        }
        
        puts("Yes");
        end:;
    }
    return 0;
}