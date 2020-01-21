#include <cstdio>
#include <queue>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
};
int n;
int w[310],dp[310][310];
int path[310][310];
inline int max(const int &a,const int &b){return a>b?a:b;}
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(w[i]);
    for(int len = 1;len<n;++len)
        for(int l = 1;l+len<=n;++l)
        {
            int r = l + len;
            for(int k = l;k<r;++k)
            {
                if(dp[l][k] + dp[k+1][r] + (w[l] + w[r]) * w[k] > dp[l][r])
                {
                    dp[l][r] = dp[l][k] + dp[k+1][r] + (w[l] + w[r]) * w[k];
                    path[l][r] = k;
                }
            }
        }
    printf("%d\n",dp[1][n]);
    queue<pair<int,int> > q;
    q.push(make_pair(1,n));
    while(!q.empty())
    {
        int l = q.front().first,r = q.front().second;
        q.pop();
        if(path[l][r] == 0)
            continue;
        printf("%d ",path[l][r]);
        q.push(make_pair(l,path[l][r]));
        q.push(make_pair(path[l][r] + 1,r));
    }
    return 0;
}