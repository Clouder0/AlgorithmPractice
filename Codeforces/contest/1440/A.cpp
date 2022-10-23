#include <cstdio>
#include <algorithm>
using namespace std;
int T,n,c0,c1,h;
char s[10000];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d %d %d %s",&n,&c0,&c1,&h,s + 1);
		int num0 = 0,num1 = 0;
		for(int i = 1;i<=n;++i) num0 += s[i] == '0',num1 += s[i] == '1';
		printf("%d\n",min(num0 * c0 + num1 * c1,min(num0 * h + n * c1,num1 * h + n * c0)));
	}
	return 0;
}
