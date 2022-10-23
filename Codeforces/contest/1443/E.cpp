#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 100;
#define int long long 
int n, m, a[maxn], vis[100], up;
long long prod[maxn], rnk;
void update()
{
	long long tmp = rnk;
	for(int j = 1;j<=up;++j) vis[j] = 0;
	for(int j = 1; j <= up; ++j) 
	{
		long long nowrnk = tmp / prod[up - j] + 1;
		tmp %= prod[up - j];
		for(int k = 1; k <= up; ++k) if(!vis[k] && --nowrnk == 0)  { a[j] = k, vis[k] = 1; break; }
	}
}
signed main()
{
	scanf("%lld %lld", &n, &m);
	up = std::min(n,15ll);
	prod[0] = 1;
	for(int i = 1; i <= 20; ++i) prod[i] = prod[i-1] * i, a[i] = i;
	if(n <= 15)
	{
		for(int i = 1, opt, l, r, x; i <= m; ++i) 
		{
			scanf("%lld", &opt);
			if(opt == 1) 
			{
				scanf("%lld %lld", &l, &r);
				int res = 0;
				for(int j = l; j <= r; ++j) res += a[j];
				printf("%lld\n", res);
			}
			else
			{
				scanf("%lld", &x);
				rnk += x;
				update();
			}
		}
		return 0;
	}
	int end = n - 15;
	for(int i = 1, opt, l, r, x; i<= m; ++i)
	{
		scanf("%lld", &opt);
		if(opt == 1)
		{
			scanf("%lld %lld", &l, &r);
			if(r <= end) printf("%lld\n", 1ll * (l + r) * (r - l + 1) >> 1);
			else if(l <= end)
			{
				long long res = (l + end) * (end - l + 1) >> 1;
				for(int j = 1;j <= r - end;++j) res += end + a[j];
				printf("%lld\n", res);
			}
			else
			{
				l -= end,r -= end;
				long long res = 0;
				for(int j = l;j<=r;++j) res += end + a[j];
				printf("%lld\n",res);
			}
		}
		else
		{
			scanf("%lld",&x);
			rnk += x;
			update();
		}
	}
	return 0;
}
/*
50 2
2 97965
1 25 42

*/
