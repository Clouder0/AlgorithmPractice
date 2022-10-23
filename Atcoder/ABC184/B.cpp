#include <cstdio>
const int maxn = 2e5 + 100;
int n,x;
char s[maxn];
int main()
{
	scanf("%d %d",&n,&x);
	scanf("%s",s + 1);
	for(int i = 1;i<=n;++i)
	{
		if(s[i] == 'o') ++x;
		else --x,x = x < 0 ? 0 : x;
	}
	printf("%d\n",x);
	return 0;
}
