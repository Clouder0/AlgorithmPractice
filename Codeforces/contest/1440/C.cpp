#include <cstdio>
#include <algorithm>
int T,n,m,a[110][110];
int X[1000000],Y[1000000],cnt;
char s[110];
inline void add(int x,int y)
{
	X[++cnt] = x,Y[cnt] = y,a[x][y] ^= 1;
}
void solve(int n,int m)
{
	int num = a[n][m] + a[n-1][m] + a[n][m-1] + a[n-1][m-1];
		if(num == 4)
		{
			add(n,m),add(n-1,m),add(n,m-1);
			goto one;
		}
		else if(num == 3)
		{
			three:
			if(a[n][m]) add(n,m);
			if(a[n-1][m]) add(n-1,m);
			if(a[n][m-1]) add(n,m-1);
			if(a[n-1][m-1]) add(n-1,m-1);
		}
		else if(num == 2)
		{
			two:
			bool aa = 0,b = 0,c = 0,d = 0;
			if(!a[n][m]) add(n,m),aa = 1;
			if(!a[n-1][m]) add(n-1,m),b = 1;
			if(!a[n][m-1]) add(n,m-1),c = 1;
			if(!a[n-1][m-1]) add(n-1,m-1),d = 1;
			if(!aa && a[n][m]) add(n,m);
			else if(!b && a[n-1][m]) add(n-1,m);
			else if(!c && a[n][m-1]) add(n,m-1);
			else if(!d && a[n-1][m-1]) add(n-1,m-1);
			goto three;
		}
		else if(num == 1)
		{
			one:
			if(a[n][m]) add(n,m),add(n-1,m),add(n,m-1);
			else if(a[n-1][m]) add(n-1,m),add(n,m),add(n,m-1);
			else if(a[n][m-1]) add(n,m-1),add(n,m),add(n-1,m-1);
			else if(a[n-1][m-1]) add(n-1,m-1),add(n,m),add(n,m-1);
			goto two;
		}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&n,&m);
		cnt = 0;
		for(int i = 1;i<=n;++i)
		{
			scanf("%s",s + 1);
			for(int j = 1;j<=m;++j) a[i][j] = s[j] - '0';
		}
		for(int i = 1;i<= n - 2;++i) for(int j = 1;j<=m;++j)
		{
			if(a[i][j]) 
			{
				add(i,j);
				add(i+1,j);
				if(j == m) add(i+1,j-1);
				else add(i+1,j+1);
			}
		}
		for(int j = 1;j<=m-2;++j) 
		{
			if(a[n-1][j] && a[n][j]) add(n-1,j),add(n,j),add(n-1,j + 1);
			else if(a[n-1][j]) add(n-1,j),add(n-1,j+1),add(n,j+1);
			else if(a[n][j]) add(n,j),add(n-1,j+1),add(n,j+1);
		}

		solve(n,m);
		printf("%d\n",cnt / 3);
		for(int i = 1;i<=cnt;++i) 
		{
			printf("%d %d ",X[i],Y[i]);
			if((i % 3) == 0) puts("");
		}
		//for(int i = 1;i<=n;puts(""),++i) for(int j = 1;j<=m;++j) printf("%d ",a[i][j]);
	}
	return 0;
}
