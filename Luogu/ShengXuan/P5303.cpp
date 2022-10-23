#include <cstdio>
int T,n;
const int maxn = 100;
int f[maxn][3];
int main()
{
	scanf("%d",&T);
	f[1][0] = 1,f[1][1] = 1,f[2][0] = 2,f[2][1] = 1,f[3][0] = 3,f[3][1] = 3,f[3][2] = 2;
	for(int i = 4;i<=100;++i)
	{
		f[i][0] = f[i-1][0] + f[i-2][0];
		f[i][1] = f[i-2][1] + f[i-1][0];
		f[i][2] = f[i-1][2] + f[i-2][2] + 2 * f[i-3][1] + 2 * f[i-2][1];
	}
	while(T--)
	{
		scanf("%d",&n);
		printf("%d\n",f[n][2]);
	}
	return 0;
}
