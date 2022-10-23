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
const int maxm = 4e5 + 100;
const int maxn = 2e5 + 100;
struct node
{
    int to,next;
}E[maxm];
int head[maxn],tot;
inline void add(const int &x,const int &y)
{
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int T,n,m;
int w[maxn],h[maxn],good[maxn];
int sum[maxn];
int flag;
void dfs(int u,int fa)
{
    sum[u] = w[u];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v,u);
        sum[u] += sum[v];
    }
}
void dfs2(int u,int fa)
{
    if(h[u] < -sum[u] || h[u] > sum[u] || ((sum[u] + h[u]) & 1)) flag = 1;
    good[u] = (sum[u] + h[u]) / 2;
    int goodsum = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs2(v,u);
        goodsum += good[v];
    }
    if(goodsum > good[u]) flag = 1;
}
int main()
{
    read(T);
    while(T--)
    {
        read(n),read(m);
        flag = 0;
        tot = 0;
        for (int i = 1; i <= n; ++i) head[i] = 0;
        for (int i = 1; i <= n; ++i) read(w[i]);
        for (int i = 1; i <= n; ++i) read(h[i]);
        for(int i = 1;i<n;++i)
        {
            int a,b;
            read(a),read(b),add(a,b),add(b,a);
        }
        dfs(1,0);
        dfs2(1,0);
        if(flag) puts("No");
        else puts("Yes");
    }
    return 0;
}