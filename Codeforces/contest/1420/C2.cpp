#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 3e5 + 100;
#define int long long
int T,n,a[maxn],m,ans;
inline void add(int x)
{
    if (a[x] > a[x - 1] && a[x] > a[x + 1]) ans += a[x];
    if(a[x] < a[x - 1] && a[x] < a[x + 1]) ans -= a[x];
}
inline void del(int x)
{
    if (a[x] > a[x - 1] && a[x] > a[x + 1]) ans -= a[x];
    if(a[x] < a[x - 1] && a[x] < a[x + 1]) ans += a[x];
}
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        ans = 0;
        scanf("%lld %lld",&n,&m);
        for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
        a[0] = a[n + 1] = -1;
        for (int i = 1; i <= n; ++i) add(i);
        printf("%lld\n",ans);
        while(m--)
        {
            int l,r;
            scanf("%lld %lld",&l,&r);
            if(l > r) swap(l,r);
            if(l == r) goto end;
            del(l - 1),del(l),del(l + 1);
            if(r - 1 > l + 1) del(r - 1);
            if(r > l + 1) del(r);
            if(r + 1 > l + 1) del(r + 1);
            swap(a[l],a[r]);
            add(l - 1),add(l),add(l + 1);
            if(r - 1 > l + 1) add(r - 1);
            if(r > l + 1) add(r);
            if(r + 1 > l + 1) add(r + 1);
            end:
            printf("%lld\n",ans);
        }
    }
    return 0;
}