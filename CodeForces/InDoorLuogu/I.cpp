#include <cstdio>
#include <queue>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e6 + 10000;
struct node
{
    int to,next;
    node(){}
    node(const int &_to,const int &_next) : to(_to),next(_next){}
}E[maxn];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot] = node(y,head[x]),head[x] = tot;
}
bool hasfa[maxn];
int dep[maxn];
int n;
int main()
{
    read(n);
    int ls,rs;
    for(int i = 1;i<=n;++i)
    {
        read(ls);
        read(rs);
        if(ls)
            add(i,ls),hasfa[ls] = 1;
        if(rs)
            add(i,rs),hasfa[rs] = 1;
    }
    int root = 0;
    queue<int> q;
    for(int i = 1;!root && i<=n;++i)
        if(!hasfa[i])
            root = i;
    dep[root] = 1;
    q.push(root);
    int u,v,ans = 1;
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        if(dep[u] > ans)
            ans = dep[u];
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            dep[v] = dep[u] + 1;
            q.push(v);
        }
    }
    printf("%d",ans);
    return 0;
}