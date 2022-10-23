#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int T,x;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&x);
		int t = sqrt(x * 2);
		while(t * (t+1)/2 < x) ++t;
		printf("%d\n",t + (t *(t+1)/2 == (x + 1)));
	}
	return 0;
}
