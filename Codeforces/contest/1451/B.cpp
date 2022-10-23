#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 110;
int T,n,m;
char s[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&n,&m);
		scanf("%s", s + 1);
		for(int i = 1,l,r;i<=m;++i)
		{
			scanf("%d %d",&l,&r);
			for(int i = 1;i < l;++i) if(s[i] == s[l]) goto YES;
			for(int i = r + 1;i <= n;++i) if(s[i] == s[r]) goto YES;
			goto NO;
			YES:puts("YES");continue;
			NO:puts("NO");continue;
			
			
		}
	}
	return 0;
}
