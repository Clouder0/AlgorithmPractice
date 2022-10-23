#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 100;
const int mod = 998244353;
inline int add(int x,int y){int res = x + y;return res >= mod ? res - mod : res;}
inline int mul(int x,int y){return 1ll * x * y % mod;}
int n,m,x,y;
int prod[maxn],prodinv[maxn],inv[maxn];
inline int C(int n,int m){return mul(prod[n],mul(prodinv[n-m],prodinv[m]));}
inline int calc(int n,int m) {return  m <= 0 ? 1 : C(n + m - 1,n - 1);}
//m into n
int main()
{
	scanf("%d %d %d %d",&m,&n,&x,&y);
	prod[0] = prodinv[0] = prod[1] = prodinv[1] = inv[1] = 1;
	for(int i = 2;i<=n + m;++i) prod[i] = mul(prod[i-1],i),prodinv[i] = mul(prodinv[i-1],inv[i] = mul(inv[mod%i],mod - mod / i));
	if(x > y) std::swap(x,y);
	if(y > n && x > n) y -= n,x -= n;
	if(x <= n && y <= n)
	{
		int ans = 0;
		for(int h = 1;h <= m;++h) 
			ans = add(ans,mul(mul(calc(h,x - 1),calc(m - h + 1,n - y)),calc(m,n)));
		printf("%d\n",ans);
	}
	else
	{
		int ans = 0;
		for(int h = 1;h<=m;++h) 
			ans = add(ans, mul(mul(mul(
				calc(h,x - 1),calc(h,2*n - y)),
				calc(m - h + 1,n - x)),calc(m - h + 1,y - n - 1)));
		printf("%d\n",ans);
	}
	return 0;
}

