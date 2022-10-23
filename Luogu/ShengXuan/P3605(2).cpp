#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 100;
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
int n,a[maxn],H[maxn],cnt;
int sum[maxn << 5],L[maxn << 5],R[maxn << 5],root[maxn],ind;
inline void pushup(const int &p){sum[p] = sum[L[p]] + sum[R[p]];}
void modify(int l,int r,int &p,int pos,int k)
{
    if(!p) p = ++ind;
    if(l == r) return (void)(sum[p] += k);
    int mid = l + r >> 1;
    if(pos <= mid) modify(l,mid,L[p],pos,k);
    else modify(mid + 1,r,R[p],pos,k);
    pushup(p);
}
int ask(int l,int r,int p,int ll,int rr)
{
    if(!p) return 0;
    if(l >= ll && r <= rr) return sum[p];
    int mid = l + r >> 1,ans = 0;
    if(ll <= mid) ans = ask(l,mid,L[p],ll,rr);
    if(rr > mid) ans += ask(mid + 1,r,R[p],ll,rr);
    return ans;
}
int merge(int l,int r,int x,int y)
{
    if(!x || !y) return x + y;
    if(l == r) {sum[x] += sum[y];return x;}
    int mid = l + r >> 1;
    L[x] = merge(l,mid,L[x],L[y]),R[x] = merge(mid + 1,r,R[x],R[y]);
    pushup(x);
    return x;
}
int res[maxn];
void dfs(int u)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        dfs(v),root[u] = merge(1,cnt,root[u],root[v]);
    }
    res[u] = ask(1,cnt,root[u],a[u] + 1,cnt);
}
int main()
{
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) scanf("%d",a + i),H[++cnt] = a[i];
    sort(H + 1,H + 1 + cnt),cnt = unique(H + 1,H + 1 + cnt) - H - 1;
    for (int i = 1; i <= n; ++i) a[i] = lower_bound(H + 1,H + 1 + cnt,a[i]) - H;
    for (int i = 1; i <= n; ++i) modify(1,cnt,root[i],a[i],1);
    for(int i = 2,x;i<=n;++i) scanf("%d",&x),add(x,i);
    dfs(1);
    for (int i = 1; i <= n; ++i) printf("%d\n",res[i]);
    return 0;
}