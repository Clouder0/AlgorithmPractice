#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 5e5 + 100;
int n,k,a[maxn];
priority_queue<long long> q;
int main()
{
	scanf("%d %d",&n,&k);
	for(int i = 1;i<=n;++i) scanf("%d",a + i);
	sort(a + 1,a + 1 + n);
	for(int i = 1;i<=k + 1;++i) q.push(0ll);
	long long res = 0;
	for(int i = n;i;--i)
	{
		long long t = q.top();
		q.pop(),res += t,q.push(t + a[i]);
	}
	printf("%lld\n",res);
	return 0;
}
