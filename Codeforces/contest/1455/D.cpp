#include <cstdio>
#include <algorithm>
using namespace std;
int T,n,x,a[11000];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&n,&x);
		for(int i = 1;i<=n;++i) scanf("%d",a + i);
		int res = 0;
		for(int i = 1;i<=n;++i) if(a[i] > x) 
		{
			bool flag = 0;
			for(int i = 1;i<n;++i) if(a[i] > a[i+1]) flag = 1;
			if(!flag) break;
			std::swap(a[i],x),++res;
		}
		for(int i = 1;i<n;++i) if(a[i] > a[i+1]) goto no;
		printf("%d\n",res);continue;
		no: puts("-1");
	}
	return 0;
}
