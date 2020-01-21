#include <cstdio>
using namespace std;
inline int max(const int &a,const int &b){return a>b?a:b;}
const int maxn = 1e5 + 10;
int T,n;
int all[maxn];
long long dp[maxn];
long long asum;
int l[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        asum = 0;
        scanf("%d",&n);
        for(int i = 1;i<=n;++i)
        {
            scanf("%d",all+i);
            asum += all[i];
        }
        for(int i = 1;i<=n;++i)
        {
            dp[i] = all[i];
            if(dp[i-1] > 0)
            {
                dp[i] += dp[i-1];
                l[i] = l[i-1];
            }
            else
                l[i] = i;
            if(dp[i] >= asum && !(i == n && l[i] == 1))
            {
                printf("No\n");
                goto end;
            }
        }
        printf("Yes\n");
        end:;
    }
    return 0;
}