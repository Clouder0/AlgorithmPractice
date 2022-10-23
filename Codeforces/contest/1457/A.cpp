#include <cstdio>
#include <algorithm>
using namespace std;
int T,n,m,r,c;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d %d %d",&n,&m,&r,&c);
		printf("%d\n",max(r - 1 + c - 1,max(n - r + c - 1,max(r - 1 + m - c,n - r + m - c))));
	}
	return 0;
}
