#include <cstdio>
#include <algorithm>
const int maxn = 2e5 + 100;
int T,n,a[maxn],s[maxn],top;
long long W,mid;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %lld",&n,&W);
		top = 0;
		for(int i = 1;i<=n;++i) scanf("%d",a + i);
		mid = (W + 1) / 2;
		long long now = 0;
		for(int i = 1;i<=n;++i) if(a[i] <= W && a[i] >= mid){printf("1\n%d\n",i);goto end;}
		for(int i = 1;i<=n;++i)
		{
			if(a[i] > W) continue;
			s[++top] = i, now += a[i];
			if(now >= mid)
			{
				printf("%d\n",top);
				while(top) printf("%d ",s[top--]);
				puts("");
				goto end;
			}
		}
		puts("-1");
		end:;
	}
	return 0;
}
