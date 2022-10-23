#include <cstdio>
#include <vector>
using namespace std;
vector<int> all[10100];
int dp[10100];
int n, k,p,t;
int main()
{
    scanf("%d%d",&n,&k);
    for (; k; --k)
    {
        scanf("%d%d",&p,&k);
        all[p].push_back(t);
    }
    for (int i = n; i; --i)
    {
        if(all[i].empty())
            dp[i] = dp[i+1] + 1;
        else
            for(vector<int>::iterator it = all[i].begin();it!=all[i].end();++it)
                if(dp[i + *it] > dp[i])
                    dp[i] = dp[i + *it];
    }
    printf("%d", dp[1]);
    return 0;
}