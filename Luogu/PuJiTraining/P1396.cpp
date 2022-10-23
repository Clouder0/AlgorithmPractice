#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e4 + 100;
struct node
{
    int from,to,next,val;
}E[maxn];
int head[maxn],tot;
inline void add(const int &x,const int &y,const int &val){E[++tot].to = y,E[tot].from = x,E[tot].next = head[x],E[tot].val = val,head[x] = tot;}
bool cmp(const node &a,const node &b){return a.val < b.val;}
int n,m,s,t;
int fa[maxn];
int find(const int &x){return fa[x] == x ? x : fa[x] = find(fa[x]);}
inline void unite(int x,int y)
{
    x = find(x),y = find(y);
    if(x == y) return;
    fa[x] = y;
}
int main()
{
    read(n),read(m),read(s),read(t);
    for(int i = 1;i<=n;++i) fa[i] = i;
    for(int i = 1;i<=m;++i)
    {
        int a,b,c;
        read(a),read(b),read(c);
        add(a,b,c);
    }
    std::sort(E+1,E+1+tot,cmp);
    for(int i = 1;i<=tot;++i)
    {
        int u = E[i].from,v = E[i].to;
        unite(u,v);
        if(find(s) == find(t))
        {
            printf("%d",E[i].val);
            return 0;
        }
    }
    return 0;
}