#include <cstdio>
#include <algorithm>
#include <cstring>
const int maxn = 1e5 + 100;
#define int long long
int n,m,opt[maxn],w[maxn];
int zero,one;
signed main()
{
	scanf("%lld %lld",&n,&m);
	for(int i = 1;i<=n;++i)
	{
		static char s[10];
		scanf("%s %lld",s + 1,w + i);
		if(s[1] == 'A') opt[i] = 1;
		else if(s[1] == 'O') opt[i] = 2;
		else opt[i] = 3;
	}
	one = (1ll << 60) - 1;
	for(int i = 1;i<=n;++i) if(opt[i] == 1) zero &= w[i], one &= w[i]; else if(opt[i] == 2) zero |= w[i], one |= w[i];
	else zero ^= w[i], one ^= w[i];
	int res = 0, now = 0;
	for(int i = 40;i >= 0;--i) 
	{
		if(zero & (1ll << i)) res += 1ll << i;
		else if(now + (1ll << i) <= m && (one & (1ll << i))) res += 1ll << i,now += 1ll << i;
	}
	printf("%lld\n",res);
	return 0;
}
