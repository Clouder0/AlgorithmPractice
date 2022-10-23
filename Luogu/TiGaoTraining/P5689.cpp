#include <cstdio>
const int maxn = 3e5 + 100;
const int mod = 1e9 + 7;
int n, m;
int prod[maxn], prodinv[maxn], inv[maxn];
inline int add(int x,int y){int res = x + y;return res >= mod ? res - mod : res;}
inline int mul(int x,int y){return 1ll * x * y % mod;}
inline int C(int n,int m){return mul(prod[n],mul(prodinv[n-m],prodinv[m]));}
int fa[maxn],f[maxn],size[maxn];
int find(int x){return fa[x] == x ? x : fa[x] = find(fa[x]);}
inline void unite(int x,int y)
{
	x = find(x),y = find(y);
	if(x == y) return;
	size[y] += size[x],f[y] = mul(f[y],mul(C(size[y] - 1,size[x]),f[x])),fa[x] = y;
}
int main()
{
	scanf("%d %d",&n,&m);
	prod[0] = prodinv[0] = prod[1] = prodinv[1] = inv[1] = 1;
	for(int i = 2;i<=n;++i) prod[i] = mul(prod[i-1],i),prodinv[i] = mul(prodinv[i-1],inv[i] = mul(mod - mod / i,inv[mod % i]));
	for(int i = 0;i<n;++i) fa[i] = i,f[i] = size[i] = 1;
	int ans = 0;
	for(int i = 1,opt,x,y;i<=m;++i)
	{
		scanf("%d %d",&opt,&x);
		if(opt == 1) scanf("%d",&y),x = (x+ans)%n,y=(y+ans)%n,unite(x,y);
		else x = (x+ans)%n,printf("%d\n",ans = f[find(x)]);
	}
	return 0;
}
