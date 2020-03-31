#include <cstdio>
#include <algorithm>
using namespace std;
template<typename T>
inline void _swap(T &a,T &b)
{
    T t = a;
    a = b;
    b = t;
}
template<typename T>
inline T read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    return r;
}
const int maxn = 2e5 + 100;
int n,m;
int a[maxn];
long long res[maxn];
bool vis[maxn];
int pp[maxn];
void dfs(int pos)
{
    if(pos > n)
    {
        long long temp = 0;
        for(int k = 1;k*2 <= n;++k)
        {
            temp = 0;
            for(int i = 1;i<=k;++i)
            {
                temp += a[pp[i]] * a[pp[i+k]];
                temp += a[pp[i]] * a[pp[n-k+i]];
            }
            for(int i = k+1;i<=n-k;++i)
            {
                temp += a[pp[i]] * a[pp[i-k]];
                temp += a[pp[i]] * a[pp[i+k]];
            }
            for(int i = n-k+1;i<=n;++i)
            {
                temp += a[pp[i]] * a[pp[i - k]];
                temp += a[pp[i]] * a[pp[i+k-n]];
            }
            temp >>= 1;
            if(temp > res[k])
                res[k] = temp;
        }
    }
    for(int i = 1;i<=n;++i)
    {
        if(vis[i])
            continue;
        pp[pos] = i;
        vis[i] = 1;
        dfs(pos+1);
        vis[i] = 0;
    }
}
int main()
{
    freopen("ring.in","r",stdin);
    freopen("ring.out","w",stdout);
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
        read(a[i]);
    if(n <= 18)
    {
        dfs(1);
        int k;
        for(int i = 1;i<=n;++i)
            res[0] += a[i] * a[i];
        for(int i = 1;i<=m;++i)
        {
            read(k);
            printf("%lld\n",res[k]);
        }
        return 0;
    }
    int k;
    for(int i = 1;i<=m;++i)
    {
        read(k);
        if(k == 1)
        {
            sort(a+1,a+1+n);
            swap(a[1],a[n-2]);
            swap(a[n-2],a[n-3]);
            long long ans = 0;
            for(int i = 1;i<n;++i)
                ans += a[i] * a[i+1];
            ans += a[1] * a[n];
            printf("%lld\n",ans);
            continue;
        }
        else if(k == 0)
        {
            long long ans = 0;
            for(int i = 1;i<=n;++i)
                ans += a[i] * a[i];
            printf("%lld\n",ans);
            continue;
        }
    }
    return 0;
}
