#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 100;
int T,n,k,a[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&n,&k);
		for(int i = 1;i<=n*k;++i) scanf("%d",a + i);
		sort(a + 1,a + 1 + n * k);
		int right = n - (n + 1) / 2;
		long long sum = 0;
		for(int i = 1;i<=k;++i) sum += a[n*k - (right+1) * (i-1) - right];
		printf("%lld\n",sum);
	}
	return 0;
}
