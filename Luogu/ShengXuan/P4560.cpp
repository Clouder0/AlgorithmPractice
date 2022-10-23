#include <cstdio>
using namespace std;
template<typename T>
inline T _min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
inline T _max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e6 + 10;
int n,m;
int maxx[maxn<<3],minn[maxn<<3],tag[maxn<<3];
inline void push_up(const int &p)
{
    maxx[p] = _max(maxx[p<<1],maxx[p<<1|1]);
    minn[p] = _min(minn[p<<1],minn[p<<1|1]);
}
inline void push_down(const int &p)
{
    if(tag[p] == -1)
        return;
    tag[p<<1] = tag[p];
    tag[p<<1|1] = tag[p];
    minn[p<<1] = maxx[p<<1] = tag[p];
    minn[p<<1|1] = maxx[p<<1|1] = tag[p];
    tag[p] = -1;
}
inline void build(const int &l,const int &r,const int &p)
{
    tag[p] = -1;
    if(l == r)
        return;
    int mid = l + r >> 1;
    build(l,mid,p<<1);
    build(mid + 1,r,p<<1|1);
}
int ll,rr,k;
inline void add(const int &l,const int &r,const int &p)
{
    if(r < l)
        return;
    if(minn[p] >= k)
        return;
    if(ll <= l && rr >= r && maxx[p] <= k)
    {
        tag[p] = k;
        minn[p] = maxx[p] = k;
        return;
    }
    push_down(p);
    int mid = l + r >> 1;
    if(ll <= mid)
        add(l,mid,p<<1);
    if(rr > mid)
        add(mid+1,r,p<<1|1);
    push_up(p);
}
inline void remove(const int &l,const int &r,const int &p)
{
    if(r < l)
        return;
    if(maxx[p] <= k)
        return;
    if(ll <= l && rr >= r && minn[p] >= k)
    {
        tag[p] = k;
        minn[p] = maxx[p] = k;
        return;
    }
    push_down(p);
    int mid = l + r >> 1;
    if(ll <= mid)
        remove(l,mid,p<<1);
    if(rr > mid)
        remove(mid+1,r,p<<1|1);
    push_up(p);
}
inline void out(const int &l,const int &r,const int &p)
{
    push_down(p);
    if(l == r)
    {
        printf("%d\n",minn[p]);
        return;
    }
    int mid = l + r >> 1;
    out(l,mid,p<<1);
    out(mid+1,r,p<<1|1);
}
int main()
{
    read(n);
    read(m);
    build(1,n,1);
    int t;
    for(int i = 1;i<=m;++i)
    {
        read(t);
        read(ll);
        read(rr);
        read(k);
        ++ll,++rr;
        if(t == 1)
            add(1,n,1);
        else
            remove(1,n,1);
    }
    out(1,n,1);
    return 0;
}