#include <cstdio>
#include <cstring>
#define int long long
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 4e5 + 100;
int n,maxC,maxm;
int a[maxn];
int f[1<<21];
int cnt[21],g[21][21];
void dfs(int status)
{
    if(f[status] != -1) return;
    if(((status - 1) & status) == 0)
    {
        f[status] = 0;
        return;
    } 
    int res = 0;
    int ans = 1ll<<60;
    for(int i = 0;i<maxC;++i)
        if((1<<i) & status)
        {
            int old = status ^ (1<<i);
            dfs(old);
            res = 0;
            for(int j = 0;j<maxC;++j) if ((1 << j) & old) res += g[i + 1][j + 1];
            if(ans > f[old] + res) ans = f[old] + res;
        }
    f[status] = ans;
}
signed main()
{
    memset(f,-1,sizeof(f));
    f[0] = 0;
    read(n);
    for(int i = 1;i<=n;++i) 
    {
        read(a[i]); 
        for(int j = 0;j<=maxC;++j) g[a[i]][j] += cnt[j];
        cnt[a[i]]++;
        maxC = a[i] > maxC ? a[i] : maxC;
    }
    maxm = (1<<maxC) - 1;
    dfs(maxm);
    printf("%lld",f[maxm]);
    return 0;
}