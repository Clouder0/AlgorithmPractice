#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 210;
struct node
{
    int to,next;
    double val;
}E[maxn * maxn];
int head[maxn];
inline void add(const int &x,const int &y,const double &val)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].next = head[x];
    E[tot].val = val;
    head[x] = tot;
}
int X[maxn],Y[maxn];
struct status
{
    int pos;
    double dis,g;
    int vis[maxn];
    status()
    {
        memset(vis,0,sizeof(vis));
    }
    bool operator<(const status &b) const
    {
        return dis + g > b.dis + b.g;
    }
}now,ne;
int n,m;
int vis[maxn];
double dis[maxn];
void dij()
{
	priority_queue<pair<double,int> ,vector<pair<double,int> >,greater<pair<double,int> > > q;
    for(int i = 1;i<=n;++i)
        dis[i] = 99999999.0;
	dis[n] = 0.0;
	q.push(make_pair(dis[n],n));
	int u,v;
	while(!q.empty())
	{
		u = q.top().second;
		q.pop();
		if(vis[u])	continue;
		vis[u] = 1;
		for(int p = head[u];p;p=E[p].next)
		{
			v = E[p].to;
			if(!vis[v] && dis[v] > dis[u] + E[p].val)
			{
				dis[v] = dis[u] + E[p].val;
				q.push(make_pair(dis[v],v));
			}
		}
	}
}
inline void Astar()
{
    priority_queue<status> qq;
    now.pos = 1;
    now.dis = 0.00;
    now.g = dis[now.pos];
    qq.push(now);
    int tot = 0;
    while(!qq.empty())
    {
        now = qq.top();
        qq.pop();
        if(now.pos == n)
            ++tot;
        if(tot == 2)
        {
            printf("%.2lf",now.dis);
            return;
        }
        int u = now.pos;
        for(int p = head[u];p;p=E[p].next)
        {
            int v = E[p].to;
            if(now.vis[v])
                continue;
            ne = now;
            ne.dis += E[p].val;
            ne.g = dis[v];
            ne.pos = v;
            ne.vis[v] = 1;
            qq.push(ne);
        }
    }
    cout << -1;
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
        read(X[i]),read(Y[i]);
    for (int i = 1; i <= m; ++i)
    {
        int u,v;
        read(u);
        read(v);
        double dist = sqrt((X[u] - X[v]) * (X[u] - X[v]) + (Y[u] - Y[v]) * (Y[u] - Y[v]));
        add(u,v,dist);
        add(v,u,dist);
    }
    dij();
    Astar();
    return 0;
}