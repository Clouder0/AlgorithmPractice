#include <cstdio>
#include <algorithm>
using namespace std;
const int mod = 998244353;
const int inv = 499122177;//inv(2)
inline int add(int x,int y){int res = x + y;return res >= mod ? res - mod : res;}
inline int mul(int x,int y)
{
	long long res = 1ll * x * y;
	return res >= mod ? res % mod : res;
}
const int maxn = 2e5 + 100;
int n,f[maxn],g[maxn][2],prod[maxn],prodinv[maxn];
int main()
{
	scanf("%d",&n);
	prod[0] = prodinv[0] = 1;
	for(int i = 1;i<=n + 1;++i) prod[i] = mul(prod[i-1],2),prodinv[i] = mul(prodinv[i-1],inv);
	f[n + 1] = 1,g[n + 1][(n + 1) & 1] = prodinv[n+1];
	for(int i = n;i;--i)
	{
		f[i] = mul(prod[i],g[i+1][(i+1) & 1]);
		g[i][0] = g[i+1][0],g[i][1] = g[i+1][1];
		g[i][i & 1] = add(g[i][i & 1],mul(prodinv[i],f[i]));
	}
	printf("%d\n",f[1]);
	return 0;
}
