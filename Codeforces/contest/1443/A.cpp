#include <cstdio>
int T,n;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i = 4 * n;i > 2 * n;i -= 2) printf("%d ",i);
		puts("");
	}
}
