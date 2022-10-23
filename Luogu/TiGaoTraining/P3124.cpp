#include <cstdio>
#include <algorithm>
using namespace std;
template<typename T>
inline T _min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
inline void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 10;
struct node
{
    int pos,size;
    bool operator<(const node &b) const
    {
        return pos < b.pos;
    }
}a[maxn];
int n,b,start;
int ans = 1<<30;
bool flag;
int main()
{
    read(n);
    read(b);
    int x,y;
    for(int i = 1;i<=n;++i)
    {
        read(a[i].size);
        read(a[i].pos);
    }
    sort(a+1,a+1+n);
    for(int i = 1;i<=n;++i)
        if(a[i].pos < b)
            start = i;
    int l = start,r = start + 1;
    int d;
    for(;l;--l)
    {
        d = a[r].pos - a[l].pos;
        while(r <= n && a[r].size < d)
        {
            ++r;
            d = a[r].pos - a[l].pos;
        }
        if(r > n)
            break;
        d = a[r].pos - a[l].pos;
        if(a[l].size >= d)
            goto noneed;
        ans = _min(ans,d - a[l].size);
    }
    l = start,r = start + 1;
    for(;r<=n;++r)
    {
        d = a[r].pos - a[l].pos;
        while(l && a[l].size < d)
        {
            --l;
            d = a[r].pos - a[l].pos;
        }
        if(!l)
            break;
        if(a[r].size >= d)
            goto noneed;
        ans = _min(ans,d - a[r].size);
    }
    if(ans == 1<<30)
        puts("-1");
    else
        printf("%d",ans);
    return 0;
    noneed:
    puts("0");
    return 0;
}