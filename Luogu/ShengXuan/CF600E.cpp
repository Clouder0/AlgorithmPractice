#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 100;
#define int long long
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
int n,root[maxn],maxx[maxn << 5],maxsum[maxn << 5],L[maxn << 5],R[maxn << 5],ind;
inline void pushup(int p)
{
    maxx[p] = max(maxx[L[p]],maxx[R[p]]);
    maxsum[p] = 0;
    if(maxx[p] == maxx[L[p]]) maxsum[p] += maxsum[L[p]];
    if(maxx[p] == maxx[R[p]]) maxsum[p] += maxsum[R[p]];
}
void modify(int l,int r,int &p,int pos,int k)
{
    if(!p) p = ++ind;
    if(l == r) return (void)(maxx[p] += k,maxsum[p] = l);
    int mid = l + r >> 1;
    if(pos <= mid) modify(l,mid,L[p],pos,k);
    else modify(mid + 1,r,R[p],pos,k);
    pushup(p);
}
int merge(int l,int r,int x,int y)
{
    if(!x || !y) return x + y;
    if (l == r) { maxsum[x] = l,maxx[x] += maxx[y]; return x; }
    int mid = l + r >> 1;
    L[x] = merge(l,mid,L[x],L[y]),R[x] = merge(mid + 1,r,R[x],R[y]),pushup(x);
    return x;
}
int ans[maxn];
void dfs(int u,int fa)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v,u),root[u] = merge(1,n,root[u],root[v]);
    }
    ans[u] = maxsum[root[u]];
}
signed main()
{
    scanf("%lld",&n);
    for (int i = 1,c; i <= n; ++i) scanf("%lld",&c),modify(1,n,root[i],c,1);
    for (int i = 1,a,b; i < n; ++i) scanf("%lld %lld",&a,&b),add(a,b),add(b,a);
    dfs(1,0);
    for (int i = 1; i <= n; ++i) printf("%lld ",ans[i]);
    return 0;
}