#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 100;
int n,a[maxn],cnt[110];
int vis[maxn * 2],last[maxn * 2],tim;
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<=n;++i) scanf("%d",a + i),cnt[a[i]]++;
	int maxx = 1;
	for(int i = 1;i<=100;++i) if(cnt[i] > cnt[maxx]) maxx = i;
	int res = 0;
	for(int t = 1;t<=100;++t)
	{
		if(t == maxx) continue;
		int now = 0;
		++tim;
		vis[now + 200000] = tim,last[now + 200000] = 0;
		for(int i = 1;i<=n;++i)
		{
			if(a[i] == maxx) ++now;
			else if(a[i] == t) --now;
			if(vis[now + 200000] == tim) res = max(res,i - last[now + 200000]);
			else vis[now + 200000] = tim,last[now + 200000] = i;
		}
	}
	printf("%d\n",res);
	return 0;
}
