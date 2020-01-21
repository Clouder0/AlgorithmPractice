#include <cstdio>
#include <vector>
#include <random>
#include <ctime>
#include <map>
using namespace std;
int n,m,T,k;
long long temp;
mt19937 rnd(137456);
inline int _abs(const int &x){return x>0?x:-x;}
inline int rd(int l,int r)
{
	return (_abs(rnd()) % (r-l+1)) + l;
}
inline long long rrd()
{
	long long temp = rnd();
	if(rd(0,1))
		temp *= -1;
	return temp;
}
vector<long long> nums;
map<long long,bool> mp;
inline void Generate_True(int k)
{
	vector<long long>all(nums);
	long long temp;
	for(int i = 1;i<=k;++i)
		all.push_back(rrd());
	k -= nums.size();
	for(int i = 0;i<k;++i)
		printf("%lld\n",all[rd(0,all.size()-1)]);
	for(vector<long long>::iterator it = nums.begin();it != nums.end();++it)
		printf("%lld\n",*it);
}
inline void Generate_False(int k)
{
	vector<long long>all;
	long long temp;
	for(int i = 1;i<=2*k;++i)
		all.push_back(rrd());
	for(int i = 0;i<k;++i)
		printf("%lld\n",all[rd(0,all.size()-1)]);
}
int main()
{
    freopen("BingoGame3.in","w",stdout);
    n = 10;
    m = 10;
	T = 10;
	printf("%d %d %d\n",n,m,T);
	int tot = 0;
	for(int i = 1;i<=n;putchar('\n'),++i)
		for(int j = 1;j<=m;++j)
			nums.push_back(++tot - 50),printf("%d ",tot-50);
	
    for(int i = 1;i<=T;++i)
	{
		k = 1000;
		printf("%d\n",k);
		for(int a = 1;a<=n;putchar('\n'),++a)
			for(int b = 1;b<=m;++b)
				printf("1 ");
		Generate_True(k);
	}
    return 0;
}
