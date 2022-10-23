#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 110;
const int maxm = 1e6;
struct node
{
	int to,next,cap;
}E[maxm];
int head[maxm],tot = 1;
inline void add(int x,int y,int cap)
{
	E[++tot].next = head[x],head[x] = tot,E[tot].to = y,E[tot].cap = cap;
	E[++tot].next = head[y],head[y] = tot,E[tot].to = x,E[tot].cap = 0;
}
int n,m,a[maxn],d[maxn][maxn],id[maxn][maxn],type[maxn*10],S,T,cnt,maxtype;
const int inf = 1 << 28;
int dep[maxm],cur[maxm];
bool bfs()
{
	static int q[maxm],qh,qt;
	for(int i = 1;i<=cnt;++i) dep[i] = 0;
	qh = 1,q[qt = 1] = S,dep[S] = 1,cur[S] = head[S];
	while(qt >= qh)
	{
		int u = q[qh++];
		if(u == T) return 1;
		for(int p = head[u],v;p;p=E[p].next) 
			if(E[p].cap && !dep[v = E[p].to]) dep[v] = dep[u] + 1,q[++qt] = v,cur[v] = head[v];
	}
	return 0;
}
long long dfs(int u,long long flow)
{
	if(!flow || u == T) return flow;
	long long vflow = 0,sumflow = 0;
	for(int &p = cur[u];p;p=E[p].next)
	{
		int v = E[p].to;
		if(E[p].cap && dep[v] == dep[u] + 1 && (vflow = dfs(v,std::min(flow,1ll * E[p].cap))))
		{
			flow -= vflow,sumflow += vflow,E[p].cap -= vflow,E[p^1].cap += vflow;
			if(flow == 0) break;
		}
	}
	return sumflow;
}
int main()
{
	scanf("%d %d",&n,&m);
	S = ++cnt,T = ++cnt;
	for(int i = 1;i<=n;++i) scanf("%d",a + i),maxtype = std::max(maxtype,a[i]);
	for(int i = 1;i<=n;++i) for(int j = i;j<=n;++j) scanf("%d",d[i] + j),id[i][j] = ++cnt;
	for(int i = 1;i<=maxtype;++i) type[i] = ++cnt;
	long long sum = 0;
	for(int i = 1;i<=maxtype;++i) add(type[i],T,m * i * i);
	for(int i = 1;i<=n;++i) add(id[i][i],type[a[i]],inf);
	for(int i = 1;i<=n;++i) d[i][i] -= a[i];
	for(int i = 1;i<=n;++i) 
	{
		for(int j = i;j<=n;++j) 
		{
			if(d[i][j] > 0)  add(S,id[i][j],d[i][j]),sum += d[i][j];
			else add(id[i][j],T,-d[i][j]);
			if(id[i][j-1] > 0) add(id[i][j],id[i][j-1],inf);
			if(id[i+1][j] > 0) add(id[i][j],id[i+1][j],inf);
		}
	}
	long long sumflow = 0;
	while(bfs()) sumflow += dfs(S,1ll << 60);
	printf("%lld\n",sum - sumflow);
	return 0;
}
