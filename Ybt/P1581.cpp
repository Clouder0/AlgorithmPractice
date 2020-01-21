#include <cstdio>
#include <set>
#include <algorithm>
#include <queue>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
struct node
{
    int to,next;
    node(){}
    node(const int &_to,const int &_next) : to(_to),next(_next){}
}lines[400010];
int head[200100];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    lines[++tot] = node(y,head[x]),head[x] = tot;
}
inline int max(const int &a,const int &b){return a>b?a:b;}
int n;
int d1[200100],d2[200100],dmax;
int dp2[200100];
void dfs(int u,int fa)
{
    int v;
    for(int p = head[u];p;p=lines[p].next)
    {
        v = lines[p].to;
        if(v == fa)
            continue;
        dfs(v,u);
        if(d1[v] + 1 > d1[u])
        {
            d2[u] = d1[u];
            d1[u] = d1[v] + 1;
        }
        else if(d1[v] + 1 > d2[u])
            d2[u] = d1[v] + 1;
    }
    if(d1[u] + d2[u] > dmax)
        dmax = d1[u] + d2[u];
}
void dfs2(int u,int fa)
{
    int num = 0,v;
    for(int p = head[u];p;p=lines[p].next)
    {
        v = lines[p].to;
        if(v == fa)
            continue;
        if(d1[v] == d1[u] + 1)
            ++num;
    }
    for(int p = head[u];p;p=lines[p].next)
    {
        v = lines[p].to;
        if(v == fa)
            continue;
        if(num > 1 || d1[u] != d1[v] + 1)
            dp2[v] = max(dp2[u],d1[u]) + 1;
        else dp2[v] = max(dp2[u],d2[u]) + 1;
        dfs2(v,u);
    }
}
int main()
{
    read(n);
    int x,y;
    for(int i = 1;i<n;++i)
    {
        read(x);
        read(y);
        ++x,++y;
        add(x,y);
        add(y,x);
    }
    dfs(1,0);
    dfs2(1,0);
    for(int i = 1;i<=n;++i)
        if(d1[i] + max(dp2[i],d2[i]) == dmax)
            printf("%d\n",i-1);
    return 0;
}