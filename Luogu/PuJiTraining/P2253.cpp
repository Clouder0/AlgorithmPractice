#include <cstdio>
using namespace std;
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e4 + 10;
struct node
{
    int l,r,len;
    int lmax,rmax,mmax;
    int lnum,rnum;
}all[maxn<<2];
int n,m;
#define ls (p<<1)
#define rs (p<<1|1)
inline void push_up(const int &p)
{
    all[p].mmax = max(all[ls].mmax,all[rs].mmax);
    all[p].lnum = all[ls].lnum;
    all[p].rnum = all[rs].rnum;
    all[p].lmax = all[ls].lmax;
    all[p].rmax = all[rs].rmax;
    if(all[ls].rnum != all[rs].lnum)
    {
        all[p].mmax = max(all[p].mmax,all[ls].rmax + all[rs].lmax);
        if (all[ls].lmax == all[ls].len)
            all[p].lmax += all[rs].lmax;
        if (all[rs].rmax == all[rs].len)
            all[p].rmax += all[ls].rmax;
    }
}
void build(const int &l,const int &r,const int &p)
{
    all[p].l = l,all[p].r = r,all[p].len = r - l + 1;
    all[p].lmax = all[p].rmax = all[p].mmax = 1;
    all[p].lnum = all[p].rnum = 0;
    if(l == r)
        return;
    int mid = (l+r)>>1;
    build(l,mid,ls);
    build(mid+1,r,rs);
    push_up(p);
}
int k;
void update(const int &l,const int &r,const int &p)
{
    if(l == r)
    {
        all[p].lnum = (all[p].rnum = (all[p].lnum^1));
        return;
    }
    int mid = (l+r)>>1;
    if(k <= mid)
        update(l,mid,ls);
    else
        update(mid+1,r,rs);
    push_up(p);
}
int main()
{
    read(n);
    read(m);
    build(1,n,1);
    for(int i = 1;i<=m;++i)
        read(k),update(1,n,1),printf("%d\n",all[1].mmax);
    return 0;
}