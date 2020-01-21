#include <cstdio>
#include <cstring>
#include <queue>
#define DEBUG
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[100000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline void read(T &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
struct node
{
    int to,next,val;
    node(){}
    node(const int &_to,const int &_next,const int &_val) : to(_to),next(_next),val(_val){}
}lines[2000];
int head[1200];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 1;
    lines[++tot] = node(y,head[x],val),head[x] = tot;
}
int n,m,s,t;
int dep[1200];
bool bfs()
{
    std::queue<int> q;
    std::memset(dep,0,sizeof(dep));
    q.push(s);
    dep[s] = 1;
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
int cur[1200];
int dfs(int now,int flow)
{
    if(now == t || !flow)
        return flow;
    int v,temp,ansflow = 0;
    for(int &p = cur[now];p;p=lines[p].next)
    {
        v = lines[p].to;
        if(dep[v] == dep[now] + 1 && lines[p].val && (temp = dfs(v,min(flow,lines[p].val))))
        {
            lines[p].val -= temp;
            lines[p^1].val += temp;
            ansflow += temp;
            if(!(flow -= temp))
                break;
        }
    }
    return ansflow;
}
int main()
{
    read(n);
    read(m);
    read(s);
    read(t);
    int x,y,z;
    for(int i = 1;i<=m;++i)
    {
        read(x);
        read(y);
        read(z);
        add(x,y,z);
        add(y,x,0);
    }
    int ans = 0,temp;
    while(bfs())
    {
        for(int i = 1;i<=n;++i)
            cur[i] = head[i];
        while((temp = dfs(s,99999999)))
            ans += temp;
    }
    printf("%d",ans);
    return 0;
}