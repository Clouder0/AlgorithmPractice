#include <cstdio>
#include <set>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e6 + 100;
int n,k;
int a[maxn];
long long ps[maxn];
bool out[maxn];
set<int> o;
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(a[i]);
    for(int i = 1;i<=n;++i)
        ps[i] = ps[i-1] + a[i];
    read(k);
    if(n == 1)
    {
        if(k - a[1] + 1> 0)
        {
            printf("%d\n",k-a[1]+1);
            for(int i = a[1];i<=k;++i)
                printf("%d ",i);
        }
        else
            puts("0");
        return 0;
    }
    for(int i = 1;i<=n;++i)
    {
        if(ps[i] > k)
            break;
        int ll = i,rr = n,mid,ans = -1;
        while(ll <= rr)
        {
            mid = (ll+rr)>>1;
            if(ps[mid] - ps[i] < ps[i])
            {
                ll = mid + 1;
                continue;
            }
            else
            {
                rr = mid - 1;
                ans = mid;
            }
        }
        //[ps[i],up)
        int up;
        if(ans == -1)
            up = k+1;
        else
            up = ps[ans] - ps[i] > k+1 ? k+1 : ps[ans] - ps[i];
        if(ps[i] >= up)
            continue;
        for(int m = ps[i];m<up;++m)
            o.insert(m);
    }
    printf("%d\n",o.size());
    for(set<int>::iterator it = o.begin();it!=o.end();++it)
        printf("%d ",*it);
    return 0;
}