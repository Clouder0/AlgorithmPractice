#include <cstdio>
#include <algorithm>
using namespace std;
#define int long long
int T,x[5],y[5],p[5];
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		for(int i = 1;i<=4;++i) scanf("%lld %lld",x + i,y + i),p[i] = i;
		long long res =  1ll << 60;
		do
		{
			int x1 = x[p[1]],x2 = x[p[2]],x3 = x[p[3]],x4 = x[p[4]];
			int y1 = y[p[1]],y2 = y[p[2]],y3 = y[p[3]],y4 = y[p[4]];
			long long now = abs(x1 - x2) + abs(x3 - x4) + abs(y1 - y3) + abs(y2 - y4);
			int l1 = min(x3,x4) - max(x1,x2),r1 = max(x3,x4) - min(x1,x2);
			int l2 = min(y2,y4) - max(y1,y3),r2 = max(y2,y4) - min(y1,y3);
			if(l1 > l2) std::swap(l1,l2),std::swap(r1,r2);
			if(r1 < l2) now += (l2 - r1) * 2;
			res = min(res,now);
		}while(next_permutation(p + 1,p + 5));
		printf("%lld\n",res);
	}
	return 0;
}
