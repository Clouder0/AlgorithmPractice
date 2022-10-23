#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 2e5 + 100;
int n,a[maxn];
int solve(vector<int> &v,int bit)
{
	if(v.size() <= 3) return 0;
	vector<int> S0,S1;
	for(vector<int>::iterator it = v.begin();it!=v.end();++it) if((*it >> bit) & 1) S1.push_back(*it); else S0.push_back(*it);
	vector<int>().swap(v);
	if(S0.size() <= 1) return solve(S1,bit - 1);
	if(S1.size() <= 1) return solve(S0,bit - 1);
	int s0 = (int)(S0.size()) - 1,s1 = (int)(S1.size()) - 1;
	return min(solve(S1,bit - 1) + s0,solve(S0,bit - 1) + s1);
}
int main()
{
	scanf("%d",&n);
	vector<int> v;
	for(int i = 1,x;i<=n;++i) scanf("%d",&x),v.push_back(x);
	printf("%d\n",solve(v,30));
	return 0;
}
