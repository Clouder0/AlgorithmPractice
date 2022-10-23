#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
const int maxn = 5e5 + 100;
const int mod = 998244353;
inline int add(int x,int y){int res = x + y;return res >= mod ? res - mod : res;}
inline int mul(int x,int y){return 1ll * x * y % mod;}
const int bufSize = 1e6;
#define DEBUG
inline char nc()
{
	#ifdef DEBUG
	return getchar();
	#endif
	static char buf[bufSize],*p1 = buf,*p2 = buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
	static char c;
	r = 0;
	for(c=nc();!isdigit(c);c=nc());
	for(;isdigit(c);c=nc()) r = r*10+c-48;
	return r;
}
struct node
{
	int to,next;
}E[maxn << 2];
int Eh[maxn],Gh[maxn],tot;
inline void addE(int x,int y){E[++tot].next = Eh[x],Eh[x] = tot,E[tot].to = y;}
inline void addG(int x,int y){E[++tot].next = Gh[x],Gh[x] = tot,E[tot].to = y;}
int n,m,dep[maxn],up[maxn];
void dfs1(int u,int fa)
{
	dep[u] = dep[fa] + 1;
	for(int p = Gh[u];p;p=E[p].next) up[u] = std::max(up[u],dep[E[p].to]);
	for(int p = Eh[u];p;p=E[p].next)
	{
		int v = E[p].to;
		if(v == fa) continue;
		dfs1(v,u);
	}
}
int f[maxn][maxn],sum[maxn][maxn];
void dfs2(int u,int fa)
{
	f[u][up[u]] = 1;
	sum[u][0] = f[u][0];
	for(int i = 1;i<=n;++i) sum[u][i] = add(sum[u][i-1],f[u][i]);
	for(int p = Eh[u];p;p=E[p].next)
	{
		int v = E[p].to;
		if(v == fa) continue;
		dfs2(v,u);
		f[u][0] = add(mul(f[u][0],f[v][0]),mul(f[u][0],sum[v][dep[u]]));
		for(int i = 1;i<dep[u];++i) 
			f[u][i] = add(mul(f[v][i],sum[u][i-1]),mul(f[u][i],add(sum[v][i],sum[v][dep[u]])));
		sum[u][0] = f[u][0];
		for(int i = 1;i<=n;++i) sum[u][i] = add(sum[u][i-1],f[u][i]);
	}
	sum[u][0] = f[u][0];
	for(int i = 1;i<=n;++i) sum[u][i] = add(sum[u][i-1],f[u][i]);
}
int main()
{
	read(n);
	for(int i = 1,a,b;i<n;++i) read(a),read(b),addE(a,b),addE(b,a);
	read(m);
	for(int i = 1,a,b;i<=m;++i) read(a),read(b),addG(a,b),addG(b,a);
	dfs1(1,0);
	//for(int i = 1;i<=n;++i) printf("up:%d %d\n",i,up[i]);
	dfs2(1,0);
	//for(int i = 1;i<=n;++i) for(int j = 0;j<=n;++j) printf("f[%d][%d]=%d\n",i,j,f[i][j]);
	printf("%d\n",f[1][0]);
	return 0;
}
