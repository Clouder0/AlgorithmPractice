#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 760;
const int mod = 1000000007;
const int many = 12345678;
int n,m,k;
int a[maxn][maxn];
long long dp[maxn][maxn];
int ls[many],rs[many],cnt;
int sum[many];
inline void push_up(const int &p)
{
    sum[p] = (sum[ls[p]] + sum[rs[p]]) % mod;
}
int target,val;
inline void add(const int &l,const int &r,const int &p)
{
    if(l == r)
    {
        sum[p] = (sum[p] + val) % mod;
        return;
    }
    int mid = l + r >> 1;
    if(mid >= target)
    {
        if(!ls[p])
            ls[p] = ++cnt;
        add(l,mid,ls[p]);
    }
    else
    {
        if(!rs[p])
            rs[p] = ++cnt;
        add(mid+1,r,rs[p]);
    }
    push_up(p);
}
int ll,rr;
inline int ask(const int &l,const int &r,const int &p)
{
    if(ll <= l && rr >= r)
        return sum[p];
    int mid = l + r >> 1;
    int ans = 0;
    if(ll <= mid)
    {
        if(!ls[p])
            ls[p] = ++cnt;
        ans = ask(l,mid,ls[p]) % mod;
    }
    if(rr > mid)
    {
        if(!rs[p])
            rs[p] = ++cnt;
        ans = (ans + ask(mid + 1,r,rs[p])) % mod;
    }
    return ans;
}
int main()
{
    read(n);
    read(m);
    read(k);
    cnt = k + 1;
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=m;++j)
            read(a[i][j]);
    dp[1][1] = 1;
    target = 1,val = 1;
    add(1,m,k + 1);
    add(1,m,a[1][1]);
    for(int i = 2;i<=n;++i)
    {
        for(int j = 2;j<=m;++j)
        {
            ll = 1,rr = j - 1;
            dp[i][j] = (ask(1,m,k + 1) - ask(1,m,a[i][j])) % mod;
        }
        for(int j = 1;j<=m;++j)
        {
            target = j,val = dp[i][j];
            add(1,m,k + 1);
            add(1,m,a[i][j]);
        }
    }
    printf("%lld",(dp[n][m] + mod) % mod);
    return 0;
}