#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 5e5 + 100;
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
int n,m,val[maxn];
char s[maxn];
struct Qe
{
    int next,id,dep;
}Q[maxn];
int Qh[maxn],ANS[maxn];
inline void addQ(int x,int dep,int id)
{
    static int tot = 0;
    Q[++tot].next = Qh[x],Qh[x] = tot,Q[tot].id = id,Q[tot].dep = dep;
}
int root[maxn],ind,sum[maxn * 4],L[maxn * 4],R[maxn * 4],st[maxn * 4],top;
inline int newnode() { return top ? st[top--] : ++ind; }
inline void delnode(int x) { sum[x] = L[x] = R[x] = 0, st[++top] = x; }
void modify(int l,int r,int &p,int pos,int k)
{
    if(!p) p = newnode();
    if (l == r) return (void)(sum[p] ^= (1 << k));
    int mid = l + r >> 1;
    if(pos <= mid) modify(l,mid,L[p],pos,k);
    else modify(mid + 1,r,R[p],pos,k);
}
int merge(int l,int r,int x,int y)
{
    if(!x || !y) return x + y;
    if(l == r) {sum[x] ^= sum[y],delnode(y);return x;}
    int mid = l + r >> 1;
    L[x] = merge(l,mid,L[x],L[y]),R[x] = merge(mid + 1,r,R[x],R[y]),delnode(y);
    return x;
}
int ask(int l,int r,int p,int pos)
{
    if(!p) return 0;
    if(l == r) return sum[p];
    int mid = l + r >> 1;
    if(pos <= mid) return ask(l,mid,L[p],pos);
    else return ask(mid + 1,r,R[p],pos);
}
int dep[maxn];
void dfs(int u)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        dep[v] = dep[u] + 1, dfs(v), root[u] = merge(1, n, root[u], root[v]);
    }
    modify(1, n, root[u], dep[u], val[u]);
    for(int p = Qh[u];p;p=Q[p].next)
    {
        int x = ask(1, n, root[u], Q[p].dep);
        int cnt = 0;
        for (int i = 0; i < 28; ++i) if ((1 << i) & x) ++cnt;
        ANS[Q[p].id] = cnt <= 1;
    }
}
int main()
{
    scanf("%d %d",&n,&m);
    for(int i = 2,x;i<=n;++i) scanf("%d",&x),add(x,i);
    scanf("%s",s + 1);
    for (int i = 1; i <= n; ++i) val[i] = s[i] - 'a';
    for (int i = 1,a,b; i <= m; ++i) scanf("%d %d",&a,&b),addQ(a,b,i);
    dep[1] = 1,dfs(1);
    for (int i = 1; i <= m; ++i) puts(ANS[i] ? "Yes" : "No");
    return 0;
}