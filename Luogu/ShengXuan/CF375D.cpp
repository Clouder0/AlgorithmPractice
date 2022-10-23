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
const int maxn = 1e5 + 100;
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
int ANS[maxn];
struct node2
{
    int id,next,k;
}Q[maxn];
int qh[maxn];
inline void addq(int x,int k,int id)
{
    static int tot =0;
    Q[++tot].next = qh[x],qh[x] = tot,Q[tot].k = k,Q[tot].id = id;
}
int n, m, c[maxn], siz[maxn], son[maxn],num[maxn],cnt[maxn];
void dfs1(int u, int fa)
{
    siz[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs1(v, u), siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}
void ins(int u,int fa)
{
    cnt[++num[c[u]]]++;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        ins(v,u);
    }
}
void del(int u,int fa)
{
    cnt[num[c[u]]--]--;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        del(v,u);
    }
}
void dfs2(int u,int fa,int keep)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa || v == son[u]) continue;
        dfs2(v, u, 0);
    }
    if (son[u]) dfs2(son[u], u, 1);
    cnt[++num[c[u]]]++;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa || v == son[u]) continue;
        ins(v,u);
    }
    for (int p = qh[u]; p; p = Q[p].next) ANS[Q[p].id] = cnt[Q[p].k];
    if(!keep)
    {
        cnt[num[c[u]]--]--;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (v == fa) continue;
            del(v, u);
        }
    }
}
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(c[i]);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    for (int i = 1, a, b; i <= m; ++i) read(a), read(b), addq(a, b, i);
    dfs1(1, 0), dfs2(1, 0, 1);
    for (int i = 1; i <= m; ++i) printf("%d\n",ANS[i]);
    return 0;
}