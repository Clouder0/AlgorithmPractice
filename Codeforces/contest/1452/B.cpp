#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 100;
int T,n,a[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		int maxx = 0;
		long long sum = 0,oldsum;
		for(int i = 1;i<=n;++i) scanf("%d",a + i),maxx = max(maxx,a[i]),sum += a[i];
		oldsum = sum;
		sum = (sum + n - 2) / (n - 1) * (n - 1);//round up
		sum = max(sum,1ll * maxx * (n - 1));
		printf("%lld\n",sum - oldsum);
	}
	return 0;
}
