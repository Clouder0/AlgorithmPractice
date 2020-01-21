#include <cstdio>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;
int n, k;
int dp[200010][610];
void solve()
{
	scanf("%d%d", &n, &k);
   	dp[0][0] = 1;
   	int i,j;
   	for (i = 1; i <= n; ++i)
       	for (j = 1; j <= k; ++j)
           	if (i >= j)
       	        dp[i][j] = (dp[i - j][j] + dp[i - 1][j - 1]) % 10086;
    printf("%d", dp[n][k]);
}
int l = 15,r = 20;
int main()
{
	string a = "partition",b = ".in",c = ".out",id;
	stringstream ss;
	for(;l<=r;++l)
	{
		memset(dp,0,sizeof(dp));
		ss.clear();
		ss << l;
		ss >> id;
    	freopen((a+id+b).c_str(),"r",stdin);
    	freopen((a+id+c).c_str(),"w",stdout);
    	solve();
		fclose(stdin);
    	fclose(stdout);
	}
    return 0;
}
