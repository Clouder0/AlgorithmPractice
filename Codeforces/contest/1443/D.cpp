#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 100;
int T,n,a[maxn],b[maxn],c[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i = 1; i <= n; ++i) scanf("%d",a + i);
		b[0] = 1 << 30;
		for(int i = 1;i<=n;++i) b[i] = min(b[i-1],a[i] - c[i-1]),c[i] = a[i] - b[i];
		for(int i = 1;i<=n;++i) if(c[i] < c[i-1] || c[i] < 0) goto fail;
		for(int i = 1;i<=n;++i) if(b[i] > b[i-1] || b[i] < 0) goto fail;
		puts("Yes");continue;
		fail:puts("No");
	}
	return 0;
}
