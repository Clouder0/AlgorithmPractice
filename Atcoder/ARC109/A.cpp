#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 1e4;
struct node
{
	int to,next,val;
}E[maxn];
int head[maxn],tot;
inline void add(int x,int y,int w){E[++tot].next = head[x],head[x] = tot,E[tot].to = y,E[tot].val = w;}
int a,b,x,y;
int dis[maxn],vis[maxn];
int main()
{
	scanf("%d %d %d %d",&a,&b,&x,&y);
	for(int i = 1;i<100;++i) add(i,i + 1,y),add(i + 1,i,y);
	for(int i = 1;i<=100;++i) add(i,i + 100,x),add(i + 100,i,x);
	for(int i = 1;i<100;++i) add(i + 1,i + 100,x),add(i + 100,i + 1,x);
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
	for(int i = 1;i<=200;++i) dis[i] =  1<<30;
	dis[a] = 0;
	q.push(make_pair(0,a));
	while(q.size())
	{
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int p = head[u];p;p=E[p].next)
		{
			int v = E[p].to;
			if(!vis[v] && dis[v] > dis[u] + E[p].val)
			{
				dis[v] = dis[u] + E[p].val,q.push(make_pair(dis[v],v));
			}
		}
	}
	printf("%d\n",dis[100 + b]);
	return 0;
}
