#include <cstdio>
#include <cstring>
using namespace std;
int n;
int all[100000][10];
int temp[10];
int cnt;
void dfs(int nown,int nowk)
{
	if(nowk == 10 && nown == n)
	{
		memcpy(all[++cnt],temp,sizeof(temp));
		return;
	}
	if(3*(10-nowk) < n - nown || 10 - nowk > n - nown)	return;//ºÙ÷¶
	for(int i = 1;i<=3;++i)
	{
		temp[nowk] = i;
		dfs(nown+i,nowk+1);
	}
}
int main()
{
	scanf("%d",&n);
	if(n > 30 || n < 10)
	{
		printf("0");
		return 0;
	}
	dfs(0,0);
	printf("%d\n",cnt);
	for(int i = 1;i<=cnt;++i)
	{
		for(int j = 0;j<10;++j)
			printf("%d ",all[i][j]);
		printf("\n");
	}
	return 0;
}
