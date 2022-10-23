#include <cstdio>
using namespace std;
template<typename T>
inline T _max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
inline T _min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 5e4 + 100;
struct node
{
    int l,r,len,mid;
    int lmax,rmax;
    int mmax;
    int lazy;
}a[maxn<<2];
int n,m;
inline void push_up(const int &p)
{
    node &now = a[p],&ls = a[p<<1],&rs = a[p<<1|1];
    now.lmax = ls.lmax;
    if(ls.lmax == ls.len)
        now.lmax += rs.lmax;
    now.rmax = rs.rmax;
    if(rs.rmax == rs.len)
        now.rmax += ls.rmax;
    now.mmax = _max(ls.mmax,rs.mmax);
    now.mmax = _max(now.mmax,ls.rmax + rs.lmax);
}
inline void push_down(const int &p)
{
    node &now = a[p],&ls = a[p<<1],&rs = a[p<<1|1];
    if(now.lazy == -1)
        return;
    if(now.lazy)
    {
        ls.lmax = ls.rmax = ls.mmax = 0;
        rs.lmax = rs.rmax = rs.mmax = 0;
        ls.lazy = rs.lazy = 1;
        now.lazy = -1;
    }
    else
    {
        ls.lmax = ls.rmax = ls.mmax = ls.len;
        rs.lmax = rs.rmax = rs.mmax = rs.len;
        ls.lazy = rs.lazy = 0;
        now.lazy = -1;
    }
}
void build(int l,int r,int p)
{
    a[p].l = l,a[p].r = r,a[p].len = r - l + 1,a[p].mid = l + r >> 1;
    a[p].lmax = a[p].rmax = a[p].mmax = a[p].len;
    a[p].lazy = -1;
    if(l == r)
        return;
    build(l,a[p].mid,p<<1);
    build(a[p].mid + 1,r,p<<1|1);
    push_up(p);
}
int tarLen;
int ask(int p)
{
    node &now = a[p],&ls = a[p<<1],&rs = a[p<<1|1];
    push_down(p);
    if(ls.mmax >= tarLen)
        return ask(p<<1);
    if(ls.rmax + rs.lmax >= tarLen)
        return ls.r - ls.rmax + 1;
    if(rs.mmax >= tarLen)
        return ask(p<<1|1);
    return 0;
}
int ll,rr,k;
void modify(int p)
{
    node &now = a[p],&ls = a[p<<1],&rs = a[p<<1|1];
    if(now.l >= ll && now.r <= rr)
    {
        if(k)
        {
            now.lmax = now.rmax = now.mmax = 0;
            now.lazy = 1;
        }
        else
        {
            now.lmax = now.rmax = now.mmax = now.len;
            now.lazy = 0;
        }
        return;
    }
    push_down(p);
    if(ll <= now.mid)
        modify(p<<1);
    if(rr > now.mid)
        modify(p<<1|1);
    push_up(p);
}
int main()
{
    read(n);
    read(m);
    build(1,n,1);
    int t,x,y;
    while(m--)
    {
        read(t);
        read(x);
        if(t == 1)
        {
            tarLen = x;
            ll = ask(1);
            printf("%d\n",ll);
            if(!ll)
                continue;
            rr = ll + tarLen - 1;
            k = 1;
            modify(1);
        }
        else
        {
            read(y);
            ll = x,rr = x + y - 1,k = 0;
            modify(1);
        }
    }
    return 0;
}