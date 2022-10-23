#include <cstdio>
#include <cmath>
#define im int mid = ((l+r)>>1)
#define MAX(x,y) ((x)>(y)?(x):(y))
using namespace std;
template<typename T>
void read(T &r)
{
    static char c; r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
inline void swap(int &a,int &b)
{
    int t = a;
    a = b;
    b = t;
}
const int maxn = 100010;
long long sum[maxn<<2];
long long maxx[maxn<<2];
int n,m;
void push_up(const int &p)
{
    sum[p] = sum[p<<1] + sum[p<<1|1];
    maxx[p] = MAX(maxx[p<<1],maxx[p<<1|1]);
}
void build(const int &l,const int &r,const int &p)
{
    if(l == r)
    {
        read(sum[p]);
        maxx[p] = sum[p];
        return;
    }
    im;
    build(l,mid,p<<1);
    build(mid+1,r,p<<1|1);
    push_up(p);
}
int ll,rr;
void change(const int &l,const int &r,const int &p)
{
    if(l == r)
    {
        sum[p] = maxx[p] = sqrt(sum[p]);
        return;
    }
    im;
    if(ll <= mid && maxx[p<<1]>1) change(l,mid,p<<1);
    if(rr > mid && maxx[p<<1|1]>1) change(mid+1,r,p<<1|1);
    push_up(p);
}
long long ask(const int &l,const int &r,const int &p)
{
    if(l >= ll && r <= rr) return sum[p];
    im;
    long long ans = 0;
    if(ll <= mid) ans += ask(l,mid,p<<1);
    if(rr > mid) ans += ask(mid+1,r,p<<1|1);
    return ans;
}
int main()
{
    int tot = 0;
    while(scanf("%d",&n)!=EOF)
    {
        ++tot;
        printf("Case #%d:\n",tot);
        build(1,n,1);
        read(m);
        int flag,x,y;
        while(m--)
        {
            read(flag);
            read(ll);
            read(rr);
            if(ll > rr) swap(ll,rr);
            if(flag == 0) change(1,n,1);
            else printf("%lld\n",ask(1,n,1));
        }
    }
    return 0;
}