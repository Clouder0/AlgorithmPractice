#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 6e5 + 100;
#define int long long
struct node
{
    int to,next;
}E[maxn];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
struct query
{
    int id,next,k;
}Q[maxn];
int Qh[maxn],ANS[maxn];
inline void addQ(int x,int k,int id)
{
    static int tot = 0;
    Q[++tot].next = Qh[x],Qh[x] = tot,Q[tot].id = id,Q[tot].k = k;
}
int n,m;
int dep[maxn],siz[maxn];
int root[maxn],sum[maxn << 5],L[maxn << 5],R[maxn << 5],ind;
void modify(int l,int r,int &p,int pos,int k)
{
    if(!p) p = ++ind;
    if(l == r) return (void)(sum[p] += k);
    int mid = l + r >> 1;
    if(pos <= mid) modify(l,mid,L[p],pos,k);
    else modify(mid + 1,r,R[p],pos,k);
    sum[p] = sum[L[p]] + sum[R[p]];
}
int asksum(int l,int r,int p,int ll,int rr)
{
    if(!p) return 0;
    if(l >= ll && r <= rr) return sum[p];
    int mid = l + r >> 1,res = 0;;
    if(ll <= mid) res = asksum(l,mid,L[p],ll,rr);
    if(rr > mid) res += asksum(mid + 1,r,R[p],ll,rr);
    return res;
}
int merge(int l,int r,int x,int y)
{
    if(!x || !y) return x + y;
    if (l == r) { sum[x] += sum[y]; return x; }
    int mid = l + r >> 1;
    L[x] = merge(l,mid,L[x],L[y]),R[x] = merge(mid + 1,r,R[x],R[y]),sum[x] = sum[L[x]] + sum[R[x]];
    return x;
}
void dfs(int u,int fa)
{
    siz[u] = 1,dep[u] = dep[fa] + 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v,u),siz[u] += siz[v];
        root[u] = merge(1,n,root[u],root[v]);
    }
    modify(1, n, root[u], dep[u], siz[u] - 1);
    for (int p = Qh[u]; p; p = Q[p].next)
        ANS[Q[p].id] = min(Q[p].k, dep[u] - 1) * (siz[u] - 1) + 
        asksum(1, n, root[u], dep[u] + 1, min(n, dep[u] + Q[p].k));
}
signed main()
{
    scanf("%lld %lld",&n,&m);
    for (int i = 1, a, b; i < n; ++i) scanf("%lld %lld", &a, &b), add(a, b), add(b, a);
    for (int i = 1,a,b; i <= m; ++i) scanf("%lld %lld",&a,&b),addQ(a,b,i);
    dfs(1,0);
    for (int i = 1; i <= m; ++i) printf("%lld\n",ANS[i]);
    return 0;
}