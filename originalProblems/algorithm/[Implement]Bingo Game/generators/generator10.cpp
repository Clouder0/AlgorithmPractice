#include <cstdio>
#include <vector>
#include <random>
#include <ctime>
#include <map>
using namespace std;
int n,m,T,k;
long long temp;
mt19937_64 rnd(174156);
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
    freopen("BingoGame10.in","w",stdout);
    n = 200;
    m = 200;
	T = 40;
	printf("%d %d %d\n",n,m,T);
	for(int i = 1;i<=n;putchar('\n'),++i)
		for(int j = 1;j<=m;++j)
		{
			long long temp = rrd();
			while(mp[temp])
				temp = rrd();
			mp[temp] = true;
			printf("%lld ",temp);
			nums.push_back(temp);
		}
	
    for(int i = 1;i<=T;++i)
	{
		k = 100000;
		printf("%d\n",k);
		for(int a = 1;a<=n;putchar('\n'),++a)
			for(int b = 1;b<=m;++b)
				printf("1 ");
		//if(k > nums.size() && rd(0,1))
			Generate_True(k);
		//else
		//Generate_False(k);
	}
    return 0;
}
