#include <cstdio>
#include <cmath>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e5 + 10;
int n,m;
int a[maxn];
int ll,rr,k;
double sinsum[maxn<<2],cossum[maxn<<2],tag[maxn<<2];
void pushup(const int &p)
{
    sinsum[p] = sinsum[p<<1] + sinsum[p<<1|1];
    cossum[p] = cossum[p<<1] + cossum[p<<1|1];
}
void pushdown(const int &p)
{
    if(!tag[p])
        return;
    tag[p<<1] += tag[p];
    tag[p<<1|1] += tag[p];
    double sinx = sin(tag[p]), cosx =  cos(tag[p]);
    double t1 = sinsum[p<<1] * cosx + cossum[p<<1] * sinx;
    double t2 = sinsum[p<<1|1] * cosx + cossum[p<<1|1] * sinx;
    cossum[p<<1] = cossum[p<<1] * cosx - sinsum[p<<1] * sinx;
    cossum[p<<1|1] = cossum[p<<1|1] * cosx - sinsum[p<<1|1] * sinx;
    sinsum[p<<1] = t1,sinsum[p<<1|1] = t2;
    tag[p] = 0;
}
void modify(int l,int r,int p)
{
    if(ll <= l && rr >= r)
    {
        tag[p] += k;
        double sinx = sin(k),cosx = cos(k);
        double t = sinsum[p] * cosx + cossum[p] * sinx;
        cossum[p] = cossum[p] * cosx - sinsum[p] * sinx;
        sinsum[p] = t;
        return;
    }
    pushdown(p);
    int mid = l + r >> 1;
    if(ll <= mid)
        modify(l,mid,p<<1);
    if(rr > mid)
        modify(mid + 1,r,p<<1|1);
    pushup(p);
}
double ask(int l,int r,int p)
{
    if(ll <= l && rr >= r)
        return sinsum[p];
    pushdown(p);
    int mid = l +r >> 1;
    double ans = 0;
    if(ll <= mid)
        ans += ask(l,mid,p<<1);
    if(rr > mid)
        ans += ask(mid + 1,r,p<<1|1);
    return ans;
}
void build(int l,int r,int p)
{
    if(l == r)
    {
        sinsum[p] = sin(a[l]);
        cossum[p] = cos(a[l]);
        return;
    }
    int mid = l + r >> 1;
    build(l,mid,p<<1);
    build(mid + 1,r,p<<1|1);
    pushup(p);
}
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(a[i]);
    build(1,n,1);
    read(m);
    while(m--)
    {
        int opt;
        read(opt);
        read(ll);
        read(rr);
        if(opt == 1)
            read(k),modify(1,n,1);
        else
            printf("%.1f\n",ask(1,n,1));
    }
    return 0;
}