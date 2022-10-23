#include <cstdio>
#include <algorithm>
int T,x,y;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&x,&y);
		int minn = std::min(x,y),res = minn * 2;
		x -= minn,y -= minn,x += y;
		if(x == 0) {printf("%d\n",res);continue;}
		printf("%d\n",res + 2 * x - 1);
	}
}
