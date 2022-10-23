#include <cstdio>
#include <algorithm>
const int maxn = 1e5 + 100;
int T,n,a[maxn];
int pos[maxn],val[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i = 1;i<=n;++i) scanf("%d",a+i);
		int minn = 1<<30;
		for(int i = 1;i<=n;++i) minn = std::min(minn,a[i]);
		int cnt = 0;
		for(int i = 1;i<=n;++i) if((a[i] % minn) == 0) ++cnt,pos[cnt] = i,val[cnt] = a[i];
		std::sort(val + 1,val + 1 + cnt);
		for(int i = 1;i<=cnt;++i) a[pos[i]] = val[i];
		for(int i = 1;i<n;++i) if(a[i] > a[i+1])  goto fail;
		puts("YES");
		continue;
		fail:puts("NO");
	}
	return 0;
}
