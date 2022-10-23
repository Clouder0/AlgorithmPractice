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
}E[maxn];
int head[maxn];
void add(int x,int y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
struct qnode
{
    int next,k,id;
}Q[maxn];
int qh[maxn];
inline void addq(int x,int k,int id)
{
    static int tot = 0;
    Q[++tot].next = qh[x],qh[x] = tot,Q[tot].id = id;
}
int n, m, c[maxn];
struct Seg
{
    int root[maxn],L[maxn * 30],R[maxn * 30],val[maxn * 30],ind;
    void modify(int l,int r,int &p,int pos,int k)
    {
        if(!p) p = ++ind;
        if(l == r) return (void)(val[p] += k);
        int mid = l + r >> 1;
        if (pos <= mid) modify(l, mid, L[p], pos, k);
        else modify(mid + 1, r, R[p], pos, k);
    }
    int merge(int x,int y)
    {
        if(!x || !y) return x + y;
        int p = ++ind;
        L[p] = merge(L[x], L[y]), R[p] = merge(R[x], R[y]), val[p] = val[x] + val[y];
    }
    int ask(int l,int r,int p,int pos)
    {
        if(!p) return 0;
        if(l == r) return val[p];
        int mid = l + r >> 1;
        if (pos <= mid) return ask(l, mid, L[p], pos);
        else return ask(mid + 1, r, R[p], pos);
    }
} A, B;
void dfs(int u,int fa)
{
    A.modify(1, n, A.root[u], c[u], 1);
    B.modify(1, n, B.root[u], A.ask(1, n, A.root[u], c[u]), 1);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v, u), B.root[u] = B.merge(B.root[u], B.root[v]);
    }
}
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(c[i]);
    for (int i = 1, a, b; i < n; ++i) add(a, b), add(b, a);

    return 0;
}