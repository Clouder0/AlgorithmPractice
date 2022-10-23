#include <cstdio>
#include <algorithm>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 10;
const int mod = 1e8 - 3;
int n;
struct node
{
    int id,val;
    bool operator<(const node &t) const
    {
        return this-> val < t.val;
    }
}a[maxn],b[maxn];
int c[maxn];
int d[maxn];
int ans;
void merge(int l,int r)
{
    if(l >= r)
        return;
    int mid = l + r >> 1;
    merge(l,mid);
    merge(mid+1,r);
    int p = l,q = mid + 1,k = l;
    while(p <= mid && q <= r)
        if(c[p] <= c[q])
            d[k++] = c[p++];
        else
            ans = (ans + mid - p + 1) % mod,d[k++] = c[q++];
    while(p <= mid) d[k++] = c[p++];
    while(q <= r) d[k++] = c[q++];
    for(int i = l;i<=r;++i)
        c[i] = d[i];
}
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(a[i].val),a[i].id = i;
    for(int i = 1;i<=n;++i)
        read(b[i].val),b[i].id = i;
    sort(a+1,a+1+n);
    sort(b+1,b+1+n);
    for(int i = 1;i<=n;++i)
        c[a[i].id] = b[i].id;
    merge(1,n);
    printf("%d",ans);
    return 0;
}