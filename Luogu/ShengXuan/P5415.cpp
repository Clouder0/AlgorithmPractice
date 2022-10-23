#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 25;
int T,n,m,k;
int f[maxn][maxn],row,col;
long double a[maxn*maxn][maxn*maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		col = row = 0;
		scanf("%d %d %d",&n,&m,&k);
		memset(a,0,sizeof(a));
		for(int i = 1;i<=n;++i) for(int j = 0;j<=m;++j) f[i][j] = ++col;
		++col;//constant column.
		a[++row][f[1][m]] = 1.0,a[row][col] = 1.0;
		for(int i = 2;i<=n;++i) a[++row][f[i][m]] = 1.0,a[row][col] = 0.0;
		for(int i = 5;i<=n;++i)
			for(int j = 0;j<m;++j)
				a[++row][f[i][j]] = 1.0,a[row][f[i-3][j+1]] += -0.25,a[row][f[i-3][1]] += -0.75;//!!!
		for(int j = 0;j < m; ++j) 
		{
			a[++row][f[1][j]] = 1.0,a[row][f[1][j+1]] += -0.25,a[row][f[n-2][1]] += -0.75;
			a[++row][f[2][j]] = 1.0,a[row][f[1][1]] += -0.25,a[row][f[n-2][j+1]] += -0.25,a[row][f[n-1][1]] += -0.5;
			a[++row][f[3][j]] = 1.0,a[row][f[1][1]] += -0.25,a[row][f[n-1][j+1]] += -0.25,a[row][f[n-1][1]] += -0.25,a[row][f[n][1]] += -0.25;
			a[++row][f[4][j]] = 1.0,a[row][f[1][1]] += -0.25,a[row][f[n][j+1]] += -0.25,a[row][f[n][1]] += -0.5;
		}
		//for(int i = 1;i<=row;puts(""),++i) for(int j = 1;j<=col;++j) printf("%.2f ",a[i][j]);
		for(int i = 1;i<=row;++i)
		{
			int maxx = i;
			for(int j = i + 1;j<=row;++j) if(fabs(a[j][i]) > fabs(a[maxx][i])) maxx = j;
			if(maxx != i) for(int j = 1;j<=col;++j) std::swap(a[i][j],a[maxx][j]);
			for(int j = 1;j<=row;++j)
			{
				if(i == j) continue;
				double t = a[j][i] / a[i][i];
				for(int k = 1;k<=col;++k) a[j][k] -= t * a[i][k];
			}
			/*
			printf("gauss:%d\n",i);
			for(int i = 1;i<=row;puts(""),++i) for(int j = 1;j<=col;++j) printf("%.2f ",a[i][j]);
			puts("");
			*/
		}
		printf("%.6Lf\n",a[f[k][0]][col] / a[f[k][0]][f[k][0]]);
	}
	return 0;
}
