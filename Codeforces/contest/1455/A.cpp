#include <cstdio>
#include <cstring>
using namespace std;
int T;
char s[110];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",s + 1);
		int n = strlen(s + 1);
		printf("%d\n",n);
	}
	return 0;
}
