#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 17;
int n,m,a[maxn][maxn],r,c;
int sum[maxn],d[maxn][maxn];
int f[maxn][maxn];
int b[maxn],res;
inline int myabs(int x){return x > 0 ? x : -x;}
void dfs(int pos,int num)
{
	if(num == c + 1)
	{
		for(int i = 1;i<=n;++i) sum[i] = 0;
		for(int i = 0;i<=n;++i) for(int j = 0;j<=n;++j) d[i][j] = 0,f[i][j] = 1 << 28;
		f[0][0] = 0;
		for(int i = 1;i<=n;++i) for(int j = 2;j<=c;++j) sum[i] += myabs(a[i][b[j-1]] - a[i][b[j]]);
		for(int i = 1;i<=n;++i) for(int j = i - 1;j >= 0;--j) for(int k = 1;k<=c;++k) d[j][i] += myabs(a[i][b[k]] - a[j][b[k]]);
		for(int i = 1;i<=n;++i) f[i][1] = sum[i];
		for(int k = 2;k<=r;++k)
			for(int i = 1;i<=n;++i) for(int j = 1; j < i; ++j) f[i][k] = std::min(f[i][k],f[j][k-1] + sum[i] + d[j][i]);
		for(int i = 1;i<=n;++i) if(res > f[i][r])
			res = f[i][r];
		//puts("b:");
		//for(int i = 1;i<=c;++i) printf("%d ",b[i]);
		//puts("matrix");
		//for(int i = 1;i<=n;puts(""),++i) for(int j = 1;j<=c;++j) printf("%d ",a[i][b[j]]);
		//puts("");
		//if(b[1] == 2 && b[2] == 6 && b[3] == 7)
			//puts("!!!");
		return;
	}
	for(int i = pos; m - i >= c - num;++i)
		b[num] = i,dfs(i + 1,num + 1);
}
int main()
{
	scanf("%d %d %d %d",&n,&m,&r,&c);
	for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) scanf("%d",a[i]+j);	
	res = 1 << 30;
	dfs(1,1);
	printf("%d\n",res);
	return 0;
}
