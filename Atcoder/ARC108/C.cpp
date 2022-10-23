#include <cstdio>
const int maxn = 1e6 + 100;
struct node
{
	int to,next,w;
}E[maxn];
int n,m,head[maxn],tot,c[maxn];
inline void add(int x,int y,int w) { E[++tot].next = head[x],E[tot].to = y,E[tot].lab = w,head[x] = tot; }
void dfs(int u)
{
	for(int p = head[u],v;p;p=E[p].next)
	{
		if(c[v = E[p].to]) continue;
		c[v] = (E[p].w == c[u] ? c[u] % n + 1 : E[p].w),dfs(v);
	}
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1,a,b,c;i<=m;++i) scanf("%d %d %d",&a,&b,&c),add(a,b,c),add(b,a,c);
	col[1] = 1,dfs(1);
	for(int i = 1;i<=n;++i) printf("%d\n",col[i]);
	return 0;
}
