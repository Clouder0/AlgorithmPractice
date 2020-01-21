#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
struct node
{
    int to,next,val;
    node(){}
    node(const int &_to,const int &_next,const int &_val) : to(_to),next(_next),val(_val){}
}lines[2000];
int head[1200];
int tot = 1;
inline void add(const int &x,const int &y,const int &val)
{
    lines[++tot] = node(y,head[x],val),head[x] = tot;
}
inline int min(const int &a,const int &b){return a<b?a:b;}
int n,m,s,t;
int dep[1000];
bool bfs()
{
    queue<int> q;
    memset(dep,0,sizeof(dep));
    dep[s] = 1;
    q.push(s);
    int u,v;
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        if(u == t)
            return true;
        for(int p = head[u];p;p=lines[p].next)
        {
            v = lines[p].to;
            if(lines[p].val && !dep[v])
            {
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
    }
    return dep[t];
}
int dfs(int u,int flow)
{
    if(u == t || !flow)
        return flow;
    int v,temp,ans(0);
    for(int p = head[u];p;p=lines[p].next)
    {
        v = lines[p].to;
        if(dep[v] == dep[u] + 1 && lines[p].val && (temp = dfs(v,min(flow,lines[p].val))))
        {
            ans += temp;
            lines[p].val -= temp;
            lines[p^1].val += temp;
            if(!(flow -= temp))
                break;
        }
    }
    return ans;
}
int main()
{
    scanf("%d%d",&m,&n);
    s = n+1;
    t = n+2;
    // [1,m]为左半边，[m+1,n]为右半边，n+1为源点，n+2为汇点
    int x,y;
    while(scanf("%d%d",&x,&y) != EOF && x != -1)
    {
        add(x,y,1);
        add(y,x,0);
    }
    for(int i = 1;i<=m;++i)
    {
        add(s,i,1);
        add(i,s,0);
    }
    for(int i = m+1;i<=n;++i)
    {
        add(i,t,1);
        add(t,i,0);
    }
    int ans(0),temp;
    while(bfs())
        ans += dfs(n+1,99999999);
    printf("%d\n",ans);
    for(int i = 2;i<=tot;i+=2)
        if(lines[i].to != s && lines[i^1].to != s && lines[i].to != t && lines[i^1].to != t && lines[i^1].val != 0)
            printf("%d %d\n",lines[i^1].to,lines[i].to);
    return 0;
}