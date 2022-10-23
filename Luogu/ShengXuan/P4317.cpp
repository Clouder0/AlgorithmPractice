#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int mod = 10000007;
long long f[70][70][2];
long long n;
long long dfs(int pos,int limit,int sum)
{
	if(pos == -1) return max(1,sum);
	if(f[pos][sum][limit] != -1) return f[pos][sum][limit];
	int up = limit ? (n >> pos) & 1 : 1;
	long long now = 1;
	for(int i = 0;i<=up;++i) now = now * dfs(pos - 1,limit && i == up,sum + i) % mod;
	return f[pos][sum][limit] = now;
}
int main()
{
	
	scanf("%lld",&n);
	int up = 0;
	while((1ll << up) < n) ++up;
	memset(f,-1,sizeof(f));
	printf("%lld\n",dfs(up,1,0));
	return 0;
}
