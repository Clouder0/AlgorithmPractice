#include <cstdio>
#include <algorithm>
using namespace std;
long long S,P;
int main()
{
	scanf("%lld %lld",&S,&P);
	long long up = S >> 1;
	long long l = 1,r = up,mid,ans = -1;
	while(l <= r)
	{
		mid = (l + r) >> 1;
		if(mid > P / (S - mid) + 10) {r = mid - 1;continue;}
		if(mid * (S - mid) <= P) l = mid + 1,ans = mid;
		else r = mid - 1;
	}
	if(ans == -1 || ans * (S - ans) != P) puts("No");
	else puts("Yes");
	return 0;
}
