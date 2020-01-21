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
struct line
{
    int l,r,h,mark;
    line(const int &_l = 0,const int &_r = 0,const int &_h = 0,const int &_mark = 0) : l(_l),r(_r),h(_h),mark(_mark) {}
    bool operator<(const line &b) const
    {
        return this->h < b.h;
    }
}lines[maxn<<2];
int n;
int X[maxn<<2];
int tag[maxn<<4];
long long len[maxn<<4];
inline void push_up(const int &l,const int &r,const int &x)
{
    if(tag[x])
        len[x] = X[r+1] - X[l];
    else if(l == r)
        len[x] = 0;
    else
        len[x] = len[x<<1] + len[x<<1|1];
}
int ll,rr,k;
inline void modify(int l,int r,int p)
{
    if(l >= ll && r <= rr)
    {
        tag[p] += k;
        push_up(l,r,p);
        return;
    }
    int mid = (l+r)>>1;
    if(ll <= mid)
        modify(l,mid,p<<1);
    if(rr > mid)
        modify(mid+1,r,p<<1|1);
    push_up(l,r,p);
}
int main()
{
    read(n);
    int leftx,downy,rightx,upy;
    for(int i = 1;i<=n;++i)
    {
        read(leftx);
        read(downy);
        read(rightx);
        read(upy);
        X[(i<<1)-1] = leftx;
        X[i<<1] = rightx;
        lines[(i<<1) - 1] = line(leftx,rightx,downy,1);
        lines[i<<1] = line(leftx,rightx,upy,-1);
    }
    n <<= 1;
    sort(lines+1,lines+1+n);
    sort(X+1,X+1+n);
    int num = unique(X+1,X+1+n) - X - 1;
    long long ans(0);
    for(int i = 1;i<=n;++i)
    {
        ans += len[1] * (lines[i].h - lines[i-1].h);
        ll = lower_bound(X+1,X+num,lines[i].l) - X;
        rr = lower_bound(X+1,X+num,lines[i].r) - X - 1;
        k = lines[i].mark;
        modify(1,num - 1,1);
    }
    printf("%lld\n",ans);
    return 0;
}