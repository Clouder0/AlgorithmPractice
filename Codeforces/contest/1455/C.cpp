#include <cstdio>
#include <algorithm>
using namespace std;
int T,x,y;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&x,&y);
		printf("%d %d\n",x - 1,y);
	}
}
