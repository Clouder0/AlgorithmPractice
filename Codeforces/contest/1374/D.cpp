#include <cstdio>
#include <set>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
#define int long long
const int maxn = 2e5 + 100;
int T,n,k,a[maxn];
std::multiset<int> s;
signed main()
{
    read(T);
    while(T--)
    {
        s.clear();
        read(n),read(k);
        for(int i = 1;i<=n;++i) read(a[i]),a[i] = k - (a[i] % k);
        for(int i = 1;i<=n;++i) if(a[i] != k) s.insert(a[i]);
        int ans = 0,x = 0;
        while(!s.empty())
        {
            std::set<int>::iterator it = s.lower_bound(x);
            if(it == s.end())  ans += k - x,x = 0;//找不到则归零
            else ans += *it - x + 1,x = (*it) + 1,s.erase(it);
            x %= k;
        }
        printf("%lld\n",ans);
    }
    return 0;
}