#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 100;
struct node
{
	int to,next;
}E[maxn];
int head[maxn];
inline void add(int x,int y)
{
	static int tot = 0;
	E[++tot].next = head[x],head[x] = tot,E[tot].to = y;
}
int n;
int f[maxn][3];// 0: self 1: fa 2: son
void dfs(int u,int fa)
{
	f[u][0] = 1,f[u][2] = 1 << 30;
	int sum = 0;
	for(int p = head[u];p;p=E[p].next)
	{
		int v = E[p].to;
		if(v == fa) continue;
		dfs(v,u);
		f[u][0] += min(f[v][0],min(f[v][1],f[v][2]));
		f[u][1] += min(f[v][0],f[v][2]);
		sum += min(f[v][0],f[v][2]);
	}
	for(int p = head[u];p;p=E[p].next)
	{
		int v = E[p].to;
		if(v == fa) continue;
		f[u][2] = min(f[u][2],sum - min(f[v][0],f[v][2]) + f[v][0]);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i = 1,u,v;i<n;++i) scanf("%d %d",&u,&v),add(u,v),add(v,u);
	dfs(1,0);
	printf("%d\n",min(f[1][0],f[1][2]));
	return 0;
}
