#include <cstdio>
int T,n;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		printf("%d\n",n);
		for(int i = 1;i<=n;++i) printf("%d ",i);
		puts("");
	}
	return 0;
}
