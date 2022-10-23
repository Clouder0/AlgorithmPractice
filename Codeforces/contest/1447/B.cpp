#include <cstdio>
#include <algorithm>
const int maxn = 20;
int T,n,m,a[maxn][maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&n,&m);
		for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) scanf("%d",a[i] + j);
		int num = 0,minn = 1 << 30;
		for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) num += (a[i][j] < 0),minn = std::min(minn,std::abs(a[i][j]));
		int sum = 0;
		for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) sum += std::abs(a[i][j]);
		if(num & 1) printf("%d\n",sum - 2 * minn);
		else printf("%d\n",sum);
	}
	return 0;
}
