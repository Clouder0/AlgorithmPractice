#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 100;
int T,n,k,a[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&n,&k);
		int maxx = 0;
		for(int i = 1;i<=n;++i) scanf("%d",a + i),maxx = max(maxx,a[i]);
		int res = 1 << 30;
		for(int c = 1;c<=maxx;++c)
		{
			int now = 0;
			for(int i = 1;i<=n;++i)
				if(a[i] != c) ++now,i += k - 1;
			res = min(res,now);
		}
		printf("%d\n",res);
	}
	return 0;
}
