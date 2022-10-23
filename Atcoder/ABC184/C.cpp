#include <cstdio>
#include <algorithm>
using namespace std;
int r1,c1,r2,c2;
int main()
{
	scanf("%d %d %d %d",&r1,&c1,&r2,&c2);
	r2 -= r1,c2 -= c1;
	if(r2 < 0) r2 = -r2;
	if(c2 < 0) c2 = -c2;
	if(r2 == 0 && c2 == 0) return puts("0"),0;
	int res = 3;
	int t = min(r2,c2);
	if(r2 + c2 <= 3) res = min(res,1);
	if(r2 == t && c2 == t) res = min(res,1);
	if(max(r2 - t,c2 - t) <= 3) res = min(res,2);
	if(r2 + c2 <= 6) res = min(res,2);
	if(!((r2 + c2) & 1)) res = min(res,2);
	printf("%d\n",res);
	return 0;
}
