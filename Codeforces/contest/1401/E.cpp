#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 2e5 + 100;
const int maxm = 1e6 + 100;
int n,m;
struct verseg
{
	int x,u,d;
	bool operator<(const verseg &b){return x < b.x;}
}W[maxn];
int sum[maxm];
inline int lowbit(const int &x){return x & (-x);}
inline void add(int x,int k) {for(;x<=maxm;x+=lowbit(x)) sum[x] +=k;}
inline int ask(int x)
{
	int res = 0;
	for(;x>0;x-=lowbit(x)) res += sum[x];
	return res;
}
inline int ask(int l,int r){return ask(r) - ask(l-1);}
vector<pair<int,int> > V[maxm];
int main()
{
	scanf("%d %d",&n,&m);
	long long ans = 1;
	for(int i = 1;i<=n;++i) 
	{
		int y,l,r;
		scanf("%d %d %d",&y,&l,&r);
		ans += ((r - l) == 1000000);
		V[l].push_back(make_pair(y,1));
		V[r+1].push_back(make_pair(y,-1));
	}
	for(int i = 1;i<=m;++i) 
	{
		scanf("%d %d %d",&W[i].x,&W[i].d,&W[i].u);
		ans += ((W[i].u - W[i].d) == 1000000);
	}
	std::sort(W + 1,W + 1 + m);
	int p = 0;
	for(int i = 1;i<=m;++i)
	{
		while(p <= W[i].x)
		{
			for(vector<pair<int,int> >::iterator it = V[p].begin();it!=V[p].end();++it)
				add(it->first,it->second);
			++p;
		}
		ans += ask(W[i].d,W[i].u);
	}
	printf("%lld\n",ans);
	return 0;
}
