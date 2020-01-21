#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template<typename T>
inline T _max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int T,n;
const int maxn = 2e5 + 10;
int nums[maxn<<1];
int tot;
struct node
{
    int l,r;
}all[maxn];
int maxx[maxn<<2],tag[maxn<<2];
inline void push_up(int p)
{
    maxx[p] = _max(maxx[p<<1],maxx[p<<1|1]);
}
int ll,rr,k;
inline void add(int l,int r,int p)
{
    if(l >= ll && r <= rr)
    {
        tag[p] += k;
        maxx[p] += k;
        return;
    }
    int mid = (l+r)>>1;
    if(ll < mid)
        add(l,mid,p<<1);
    if(rr > mid)
        add(mid+1,r,p<<1|1);
    push_up(p);
}
int ans = 0;
inline int binary_search(int x)
{
    int l = 1,r = tot,mid,ans;
    while(l <= r)
    {
        mid = (l+r)>>1;
        if(nums[mid] == x)
            return mid;
        else if(nums[mid] > x)
            r = mid - 1;
        else
            l = mid + 1;
    }
}
inline void solve()
{
    for(int i = 1;i<=n;++i)
    {
        ll = binary_search(all[i].l);
        rr = binary_search(all[i].r);
        k = 1;
        add(1,tot,1);
    }
    for(int i = 1;i<=n;++i)
    {
        ll = binary_search(all[i].l);
        rr = binary_search(all[i].r);
        k = -1;
        add(1,tot,1);
        ans = max(ans,maxx[1]);
        k = 1;
        add(1,tot,1);
    }
    printf("%d\n",ans);
}
inline void init()
{
    read(n);
    for(int i = 0;i<=n<<1;++i)
        nums[i] = maxx[i] = tag[i] = 0;
    for(int i = 1;i<=n;++i)
    {
        read(nums[(i<<1)-1]);
        read(nums[i<<1]);
        all[i].l = nums[(i<<1)-1];
        all[i].r = nums[i<<1];
    }
    sort(nums+1,nums+1+(n<<1));
    tot = unique(nums+1,nums+1+(n<<1)) - nums;
}
int main()
{
    read(T);
    while(T--)
    {
        init();
        solve();
    }
    return 0;
}
/*

1
4
1 4
2 3
3 6
5 7

*/