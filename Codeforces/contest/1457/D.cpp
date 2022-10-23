#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 100;
int n,a[maxn],hb[maxn],sum[maxn];
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<=n;++i) scanf("%d",a + i);
	for(int i = 1;i<=n;++i) for(int j = 30;j>=0;--j) if((a[i] >> j) & 1) { hb[i] = j; break; }
	for(int i = 1;i+2<=n;++i) if(hb[i] == hb[i+1] && hb[i+1] == hb[i+2]) {puts("1");return 0;}
	for(int i = 1;i<=n;++i) sum[i] = sum[i-1] ^ a[i];
	int res = 1 << 30;
	for(int i = 1;i<n;++i)
		for(int l = i;l;--l)
			for(int r = i + 1;r<=n;++r)
				if((sum[i] ^ sum[l-1]) > (sum[r] ^ sum[i]))
					res = min(res,i - l + r - i - 1);
	if(res > n) puts("-1");
	else printf("%d\n",res);
	return 0;
}
