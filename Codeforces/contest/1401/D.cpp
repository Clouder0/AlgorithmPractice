#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 100,maxm = 6e4 + 100;
struct node
{
	int to,next;
}E[maxn<<2];
int head[maxn],tot;
inline void add(const int &x,const int &y)
{
	E[++tot].to = y,E[tot].next = head[x],head[x] = tot;
}
const int mod = 1e9 + 7;
int T,n,m;
long long w[maxn];
int siz[maxn];
void dfs(int u,int fa)
{
	siz[u] = 1;
	for(int p = head[u];p;p=E[p].next)	if(E[p].to != fa) dfs(E[p].to,u),siz[u] += siz[E[p].to];
	w[u] = 1ll * siz[u] * (n - siz[u]);
}
int primes[maxm];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i = 1;i<=n;++i) head[i] = 0;
		tot = 0;
		for(int i = 1;i<n;++i)
		{
			int a,b;
			scanf("%d %d",&a,&b),add(a,b),add(b,a);
		}
		dfs(1,0);
		scanf("%d",&m);
		for(int i = 1;i<=m;++i) scanf("%d",primes + i);
		std::sort(w + 1,w + 1 + n);
		std::sort(primes + 1,primes + 1 + m);
		long long ans = 0;
		int p = n;
		if(m <= n - 1)
		{
			first:
			for(int i = m;i;--i) ans = (ans + 1ll * primes[i] * w[p--]) % mod;
			while(p) ans = (ans + w[p--]) % mod;
			printf("%lld\n",ans);
		}
		else
		{
			while(m > n - 1) primes[n-1] = (1ll * primes[n-1] * primes[m--]) % mod;
			goto first;
		}
	}
	return 0;
}
