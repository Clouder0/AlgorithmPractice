#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 1e5 + 100;
const int mod = 100003;
inline int add(int x,int y){int res = x + y;return res >= mod ? res - mod : res;}
inline int mul(int x,int y){return 1ll * x * y % mod;}
vector<int> frac[maxn];
int n,k,a[maxn],f[maxn],inv[maxn];
int main()
{
	scanf("%d %d",&n,&k);
	for(int i = 1;i<=n;++i) scanf("%d",a + i);
	for(int j = 1;j<=n;++j) for(int i = j;i<=n;i+=j) frac[i].push_back(j);
	int num = 0;
	for(int i = n;i;--i) if(a[i]) 
	{
		for(vector<int>::iterator it = frac[i].begin();it!=frac[i].end();++it) a[*it] ^= 1;
		++num;
	}
	if(k >= num) 
	{
		for(int i = 1;i<=n;++i) num = mul(num,i);
		printf("%d\n",num);
	}
	else
	{
		inv[1] = 1;
		for(int i = 2;i<=n;++i) inv[i] = mul(mod - mod / i,inv[mod % i]);
		f[n] = 1;
		for(int i = n - 1;i;--i) f[i] = add(mul(mul(n-i,inv[i]),f[i+1]),mul(n,inv[i]));
		int res = k;
		for(int i = num;i > k;--i) res = add(res,f[i]);
		for(int i = 1;i<=n;++i) res = mul(res,i);
		printf("%d\n",res);
	}
	return 0;
}
