#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 2e5 + 100;
char s[maxn];
int T,n,num1,num2;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",s + 1);
		n = strlen(s + 1);
		int res = 0;
		num1 = num2 = 0;
		for(int i = 1;i<=n;++i)
		{
			if(s[i] == '(') ++num1;
			else if(s[i] == ')')
			{
				if(num1) ++res,--num1;
			}
			else if(s[i] == '[') ++num2;
			else
			{
				if(num2) ++res,--num2;
			}
		}
		printf("%d\n",res);
	}
	return 0;
}
