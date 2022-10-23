#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 10;
const int maxk = 17;
int k,n;
int v[maxk];
long long s[maxn];
int f[1<<maxk];
int main()
{
    read(k);
    read(n);
    for(int i = 1;i<=k;++i)
        read(v[i]);
    for(int i = 1;i<=n;++i)
        read(s[i]),s[i] += s[i-1];
    int maxs = (1<<k) - 1;
    for(int i = 1;i<=maxs;++i)
    {
        for(int j = 1;j<=k;++j)
        {
            if(i & (1<<(j-1)))
            {
                int t = i ^ (1<<(j-1));
                if(f[t] == n)
                {
                    f[i] = n;
                    continue;
                }
                int l = f[t] + 1,r = n,mid,ans = -1;
                while(l <= r)
                {
                    mid = l + r >> 1;
                    if(s[mid] - s[f[t]] <= v[j])
                        l = mid + 1,ans = mid;
                    else
                        r = mid - 1;
                }
                if(ans == -1)
                {
                    puts("-1");
                    return 0;
                }
                if(f[i] < ans)
                    f[i] = ans;
            }
        }
    }
    int ans = 0;
    for(int i = 1;i<=maxs;++i)
        if(f[i] == n)
        {
            int value = 0;
            for(int j = 1;j<=k;++j)
                if(!(i & (1<<(j-1))))
                    value += v[j];
            ans = ans < value ? value : ans;
        }
    printf("%d",ans);
    return 0;
}