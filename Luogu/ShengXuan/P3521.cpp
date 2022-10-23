#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int maxn = 4e5 + 100;
struct node
{
    int to,next;
}E[maxn * 2];
int head[maxn],cnt;
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int allroot,n,val[maxn],ls[maxn],rs[maxn];

int root[maxn<<5],sum[maxn << 5],L[maxn << 5],R[maxn << 5],ind;
void pushup(int p){sum[p] = sum[L[p]] + sum[R[p]];}
void modify(int l,int r,int &p,int pos,int k)
{
    if(!p) p = ++ind;
    if(l == r) return (void)(sum[p] += k);
    int mid = l + r >> 1;
    if(pos <= mid) modify(l,mid,L[p],pos,k);
    else modify(mid + 1,r,R[p],pos,k);
    pushup(p);
}
int ans1,ans2;
int merge(int l,int r,int x,int y)
{
    if(!x || !y) return x + y;
    if(l == r) {sum[x] += sum[y];return x;}
    int mid = l + r >> 1;
    ans1 += sum[R[x]] * sum[L[y]];
    ans2 += sum[R[y]] * sum[L[x]];
    L[x] = merge(l,mid,L[x],L[y]),R[x] = merge(mid + 1,r,R[x],R[y]),pushup(x);
    return x;
}
int ans;
void dfs(int u)
{
    if(!ls[u]) return;
    dfs(ls[u]),dfs(rs[u]);
    ans1 = ans2 = 0,merge(1,n,root[ls[u]],root[rs[u]]);
    ans += min(ans1,ans2);
    root[u] = root[ls[u]];
}
int pointnum;
namespace IO
{
    int read()
    {
        int root,x;
        root = ++pointnum;
        scanf("%lld",&x);
        if(x != 0) modify(1,n,::root[root],x,1);
        else ls[root] = read(),rs[root] = read();
        return root;
    }
}
signed main()
{
    scanf("%lld",&n);
    allroot = IO::read();
    dfs(allroot);
    printf("%lld\n",ans);
    return 0;
}