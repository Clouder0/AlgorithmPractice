#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 100;
int T,a,b,n;
int L[maxn],R[maxn];
char s[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&a,&b);
		scanf("%s",s + 1);
		n = strlen(s + 1);
		for(int i = 1;i <= n; ++i) if(s[i] == '1') L[i] = i; else L[i] = L[i - 1];
		for(int i = n; i; --i) if(s[i] == '0') R[i] = i; else R[i] = R[i + 1];
		int res = 0;
		for(int i = 1;i <= n;++i)
		{
			if(s[i] != '1') continue;
			int last = L[i-1];
			if(last && (i - last - 1) * b < a) res += (i - last - 1) * b;
			else res += a;
			if(!R[i]) break;
			i = R[i] - 1;
		}
		printf("%d\n",res);
	}
	return 0;
}
