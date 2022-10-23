#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 100;
int n,a[maxn],times[maxn],B,s[maxn],top,vis[maxn * 2],tim,last[maxn * 2],res,cnt[maxn],tot[maxn];
inline void add(int x) { tot[cnt[a[x]]++]--,tot[cnt[a[x]]]++; }
inline void del(int x) { tot[cnt[a[x]]--]--,tot[cnt[a[x]]]++; }
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<=n;++i) scanf("%d",a + i),times[a[i]]++;
	int maxx = 1;
	for(int i = 2;i<=n;++i) if(times[i] > times[maxx]) maxx = i;
	B = std::sqrt(n);
	for(int i = 1;i<=n;++i) if(i!=maxx && times[i] > B) s[++top] = i;
	for(int t = 1,now;t<=top;++t)
	{
		now = 0,vis[200000] = ++tim,last[200000] = 0;
		for(int i = 1;i<=n;++i) 
		{
			if(a[i] == maxx) ++now; else if(a[i] == s[t]) --now;
			if(vis[now + 200000] == tim) res = max(res,i - last[now + 200000]); else vis[now+200000] = tim,last[now + 200000] = i;
		}
	}
	for(int t = 1;t<=B;++t)
	{
		for(int i = 1;i<=n;++i) tot[i] = cnt[i] = 0;
		int l = 1,r = 0;
		while(r < n)
		{
			add(++r);
			while(cnt[a[r]] > t) del(l++);
			if(tot[t] >= 2) res = max(res,r - l + 1);
		}
	}
	printf("%d\n",res);
	return 0;
}
