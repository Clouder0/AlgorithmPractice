#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 100;
struct node
{
    int from,to,val,next;
}E[maxn];
bool cmp(const node &a,const node &b){return a.val > b.val;}
int head[maxn],tot;
inline void add(const int &x,const int &y,const int &val)
{
    E[++tot].next = head[x],E[tot].from = x,E[tot].to = y,E[tot].val = val,head[x] = tot;
}
int n,m;
int fa[maxn],size[maxn];
int find(const int &x){return fa[x] == x ? x : fa[x] = find(fa[x]);}
inline void unite(int x,int y)
{
    x = find(x),y = find(y);
    if(x == y) return;
    fa[x] = y,size[y] += size[x];
}
struct query
{
    int k,v,id;
}Q[maxn];
bool cmp2(const query &a,const query &b) {return a.k > b.k;}
int ans[maxn];
int main()
{
    read(n),read(m);
    for(int i = 1;i<n;++i)
    {
        int a,b,c;
        read(a),read(b),read(c);
        add(a,b,c);
    }
    std::sort(E + 1,E + 1 + tot,cmp);
    for(int i = 1;i<=n;++i) fa[i] = i,size[i] = 1;
    for(int i = 1;i<=m;++i) read(Q[i].k),read(Q[i].v),Q[i].id = i;
    std::sort(Q + 1,Q + 1 + m,cmp2);
    int p = 1;
    for(int i = 1;i<=m;++i)
    {
        while(E[p].val >= Q[i].k) unite(E[p].from,E[p].to),++p;
        ans[Q[i].id] = size[find(Q[i].v)] - 1;
    }
    for(int i = 1;i<=m;++i) printf("%d\n",ans[i]);
    return 0;
}