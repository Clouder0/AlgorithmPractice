#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 500010;
int n,m;
struct node
{
    long long sum,lmax,rmax,max;
    int lmp,rmp,ml,mr;
    int l,r;
}all[maxn<<2];
inline void push_up(node &now,node &ls,node &rs)
{
    now.sum = ls.sum + rs.sum;
    now.lmax = ls.lmax;
    now.lmp = ls.lmp;
    if(ls.lmax == ls.sum)
        now.lmax += rs.lmax,now.lmp = rs.lmp;
    now.rmax = rs.rmax;
    now.rmp = rs.rmp;
    if(rs.rmax == rs.sum)
        now.rmax += ls.rmax,now.rmp = ls.rmp;
    now.max = ls.max;
    now.ml = ls.ml;
    now.mr = ls.mr;
    if(now.max < ls.rmax + rs.lmax)
    {
        now.max = ls.rmax + rs.lmax;
        now.ml = ls.rmp;
        now.mr = rs.lmp;
    }
    if(now.max < rs.max)
    {
        now.max = rs.max;
        now.ml = rs.ml;
        now.mr = rs.mr;
    }
}
void build(const int &l,const int &r,const int &p)
{
    all[p].l = l,all[p].r =r;
    if(l == r)
    {
        read(all[p].sum);
        all[p].lmax = all[p].rmax = all[p].max = all[p].sum;
        all[p].lmp = all[p].rmp = all[p].ml = all[p].mr = l;
        return;
    }
    int mid = (l+r)>>1;
    build(l,mid,p<<1);
    build(mid+1,r,p<<1|1);
    push_up(all[p],all[p<<1],all[p<<1|1]);
}
int ll,rr;
node ask(const int &p)
{
    node &now = all[p];
    if(ll <= now.l && rr >= now.r)
        return now;
    int mid = (now.l+now.r)>>1;
    if(ll > mid)
        return ask(p<<1|1);
    if(rr <= mid)
        return ask(p<<1);
    node ls = ask(p<<1),rs = ask(p<<1|1),res;
    res.l = ls.l;
    res.r = rs.r;
    push_up(res,ls,rs);
    return res;
}
int main()
{
    int t = 0;
    while(scanf("%d %d",&n,&m) == 2)
    {
        printf("Case %d:\n",++t);
        build(1, n, 1);
        while (m--)
        {
            read(ll);
            read(rr);
            node res = ask(1);
            printf("%d %d\n", res.ml, res.mr);
        }
    }
    return 0;
}