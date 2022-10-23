#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize],*p1,*p2;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c);) c = nc();
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
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
int n;
int root[maxn], maxx[maxn * 4], maxid[maxn * 4], L[maxn * 4], R[maxn * 4], ind;
int s[maxn*4],top;
inline int newnode() { return top ? s[top--] : ++ind; }
inline void delnode(int x) { maxx[x] = maxid[x] = L[x] = R[x] = 0, s[++top] = x; }
void pushup(int p)
{
    maxx[p] = max(maxx[L[p]],maxx[R[p]]);
    if(maxx[p] == maxx[L[p]]) maxid[p] = maxid[L[p]];
    else maxid[p] = maxid[R[p]];
}
void modify(int l,int r,int &p,int pos,int k)
{
    if(!p) p = newnode();
    if(l == r) return (void)(maxid[p] = l,maxx[p] += k);
    int mid = l + r >> 1;
    if(pos <= mid) modify(l,mid,L[p],pos,k);
    else modify(mid + 1,r,R[p],pos,k);
    pushup(p);
}
int merge(int l,int r,int x,int y)
{
    if(!x || !y) return x + y;
    if (l == r) { maxid[x] = l,maxx[x] += maxx[y], delnode(y); return x; }
    int mid = l + r >> 1;
    L[x] = merge(l, mid, L[x], L[y]), R[x] = merge(mid + 1, r, R[x], R[y]), pushup(x),delnode(y);
    return x;
}
int dep[maxn],ANS[maxn];
void dfs(int u,int fa)
{
    dep[u] = dep[fa] + 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs(v, u), root[u] = merge(1, n, root[u], root[v]);
    }
    modify(1, n, root[u], dep[u], 1);
    ANS[u] = maxid[root[u]] - dep[u];
}
signed main()
{
    read(n);
    for (int i = 1,a,b; i < n; ++i) read(a),read(b),add(a,b),add(b,a);
    dfs(1,0);
    for (int i = 1; i <= n; ++i) printf("%d\n",ANS[i]);
    return 0;
}