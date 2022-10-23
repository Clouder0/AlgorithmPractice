#include <cstdio>
#include <algorithm>
using namespace std;
int T;
int a0,a1,a2,b0,b1,b2;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d %d\n%d %d %d",&a0,&a1,&a2,&b0,&b1,&b2);
		long long ans = 0;
		int twoone = std::min(a2,b1);
		a2 -= twoone,b1 -= twoone;
		ans += twoone * 2;
		int oneone = std::min(a1,b1);
		a1 -= oneone,b1 -= oneone;
		int twotwo = std::min(a2,b2);
		a2 -= twotwo,b2 -= twotwo;
		int zerotwo = std::min(a0,b2);
		a0 -= zerotwo,b2 -= zerotwo;
		int onetwo = std::min(a1,b2);
		a1 -= onetwo,b2 -= onetwo;
		ans -= onetwo * 2;
		printf("%lld\n",ans);
	}
	return 0;
}
