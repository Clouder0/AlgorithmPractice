#include <cstdio>
#include <algorithm>
int T,n,k;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&n,&k);
		printf("%d\n",std::max(k-n,(int)((n&1)!=(k&1))));
	}
}
