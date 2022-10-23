#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
const int maxn = 2e5 + 100;
int T,n;
vector<int> v[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i = 0;i <= n;++i) v[i].clear();
		for(int i = 1,a,b;i <= n;++i) scanf("%d %d",&a,&b),v[a].push_back(b);
		multiset<int> s;
		long long cost = 0;
		int pre = n, cnt = 0;
		for(int i = n;i >= 0;--i)
		{
			//printf("%d\n",i);
			pre -= v[i].size();
			int need = i - pre - cnt;
			for(vector<int>::iterator it = v[i].begin();it!=v[i].end();++it) s.insert(*it);
			for(;need > 0;--need) ++cnt,cost += *s.begin(),s.erase(s.begin());
		}
		printf("%lld\n",cost);
	}
	return 0;
}
