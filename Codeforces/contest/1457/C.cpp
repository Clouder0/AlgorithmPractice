#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 100;
int T,n,p,k,cnt[maxn],x,y;
char a[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&n,&p,&k);
		scanf("%s",a + 1);
		scanf("%d %d",&x,&y);
		for(int i = 0;i<k;++i) cnt[i] = 0;
		int res = 1 << 30;
		for(int i = n;i >= p;--i)
		{
			cnt[i % k] += (a[i] == '0') * x;
			res = min(res,y * (i - p) + cnt[i % k]);
		}
		printf("%d\n",res);
	}
	return 0;
}
