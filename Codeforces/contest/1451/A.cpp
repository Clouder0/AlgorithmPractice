#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int T,n;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		if(n <= 3) printf("%d\n",n - 1);
		else if(n & 1) puts("3");
		else puts("2");
	}
}
