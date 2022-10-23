#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e6 + 100;
int T,n,k,cnta[30],cntb[30];
char a[maxn],b[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&n,&k);
		scanf("%s",a + 1);
		scanf("%s",b + 1);
		for(int i = 1;i<=26;++i) cnta[i] = cntb[i] = 0;
		for(int i = 1;i<=n;++i) cnta[a[i] - 'a' + 1]++;
		for(int i = 1;i<=n;++i) cntb[b[i] - 'a' + 1]++;
		for(int i = 1;i<=26;++i)
		{
			if(cnta[i] == cntb[i]) continue;
			if(cnta[i] < cntb[i]) goto NO;
			if((cntb[i] - cnta[i]) % k != 0) goto NO;
			cnta[i+1] += cnta[i] - cntb[i];
			cnta[i] = cntb[i];
		}
		puts("YES");continue;
		NO:puts("NO");
	}
	return 0;
}
