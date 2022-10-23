#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
inline char nc()
{
	static char buf[100000],*p1 = buf,*p2 = buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
void read(long long &r)
{
	static char c;
	r = 0;
	for(c=nc();c>'9'||c<'0';c=nc());
	for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
void read(int &r)
{
	static char c;
	r = 0;
	for(c=nc();c>'9'||c<'0';c=nc());
	for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
struct node
{
	int to,next;
	long long val;
	node(){}
	node(int _to,int _next,long long _val) : to(_to),next(_next),val(_val){}
}lines[400010];
int head[100010];
void add(const int &x,const int &y,const long long &val)
{
	static int tot = 0;
	lines[++tot] = node(y,head[x],val),head[x] = tot;
}
int n,m,s;
long long dis[100010];
bool vis[100010];
void dij()
{
	priority_queue<pair<long long,int>,vector<pair<long long,int> >,greater<pair<long long,int> > > q;
	memset(dis,0x3f,sizeof(dis));
	dis[s] = 0;
	q.push(make_pair(dis[s],s));
	int u,v;
	while(!q.empty())
	{
		u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int p = head[u] ;p;p=lines[p].next)
		{
			v = lines[p].to;
			if(lines[p].val + dis[u] < dis[v])
			{
				dis[v] = lines[p].val + dis[u];
				q.push(make_pair(dis[v],v));
			}
		}
	}
}
int main()
{
	//freopen("test.txt","r",stdin);
	//freopen("test.out","w",stdout);
	read(n);
	read(m);
	read(s);
    int t;
    read(t);
	int a,b,c;
	while(m--)
	{
		read(a);read(b);read(c);
		add(a,b,c);
	}
	dij();
    printf("%lld\n",dis[t]);
	return 0;
}