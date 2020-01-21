#include <cstdio>
#include <cstring>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
};
int n;
char all[110];
inline int max(const int &a,const int &b){return a>b?a:b;}
int dp[110][110];
int main()
{
    scanf("%s",all+1);
    n = strlen(all+1);
    for(int len = 1;len<=n;++len)
        for(int i = 1;i+len<=n;++i)
        {
            if((all[i] == '(' && all[i+len] == ')') || (all[i] == '[' && all[i+len] == ']'))
                dp[i][i+len] = max(dp[i][i+len],dp[i+1][i+len-1] + 2);
            for(int k = i;k<=i+len;++k)
                dp[i][i+len] = max(dp[i][i+len],dp[i][k] + dp[k+1][i+len]);
        }
    printf("%d",n - dp[1][n]);
    return 0;
}