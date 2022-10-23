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
const int maxn = 1e5 + 100;
struct node
{
    int to,next,val,id;
}E[maxn << 1];
int head[maxn];
inline void add(const int &x,const int &y,const int &val,const int &id)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, head[x] = tot, E[tot].id = id;
}
int n, fadis[maxn], fa[maxn], size[maxn], son[maxn], top[maxn], dep[maxn], dfn[maxn], id[maxn],rid[maxn],ind;
int maxx[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1 
void modify(int l,int r,int p,int pos,int k)
{
    if(l == r) return (void)(maxx[p] = k);
    int mid = l + r >> 1;
    if(pos <= mid) modify(l,mid,ls,pos,k);
    else modify(mid + 1,r,rs,pos,k);
    maxx[p] = max(maxx[ls],maxx[rs]);
}
int ask(int l,int r,int p,int ll,int rr)
{
    if(l >= ll && r <= rr) return maxx[p];
    int mid = l + r >> 1,ans = - (1 << 30);
    if(ll <= mid) ans = ask(l,mid,ls,ll,rr);
    if(rr > mid) ans = max(ans,ask(mid + 1,r,rs,ll,rr));
    return ans;
}
void dfs1(int u)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        rid[E[p].id] = v, fadis[v] = E[p].val, dep[v] = dep[u] + 1, fa[v] = u, dfs1(v), size[u] += size[v];
        if (size[son[u]] < size[v]) son[u] = v;
    }
}
void dfs2(int u)
{
    dfn[u] = ++ind,id[ind] = u;
    if (!son[u]) return;
    top[son[u]] = top[u],dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u] || v == son[u]) continue;
        top[v] = v,dfs2(v);
    }
}
void build(int l,int r,int p)
{
    if(l == r) return (void)(maxx[p] = fadis[id[l]]);
    int mid = l + r >> 1;
    build(l,mid,ls),build(mid + 1,r,rs);
    maxx[p] = max(maxx[ls],maxx[rs]);
}
int task(int x,int y)
{
    int ans = 0;
    while(top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = max(ans, ask(1, n, 1, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x,y);
    if (dfn[x] < dfn[y]) ans = max(ans, ask(1, n, 1, dfn[x] + 1, dfn[y]));
    return ans;
}
int main()
{
    read(n);
    for (int i = 1,a,b,c; i < n; ++i) read(a),read(b),read(c),add(a,b,c,i),add(b,a,c,i);
    dfs1(1), top[1] = 1, dfs2(1), build(1, n, 1);
    char s[10];
    int a,b;
    while(1)
    {
        read(s + 1);
        if(s[1] == 'D') return 0;
        if (s[1] == 'Q') read(a), read(b), printf("%d\n", task(a, b));
        else read(a), read(b), modify(1, n, 1, dfn[rid[a]], b);
    }
    return 0;
}