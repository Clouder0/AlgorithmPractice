#include <cstdio>
using namespace std;
template<typename T>
inline void swap(T &a,T &b){T t;t = a;a = b;b = t;}
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
const int maxn = 1e5 + 10;
int n,m;
struct node
{
    int lmax[2],rmax[2],maxx[2],sum;
    int l,r,len;
    int lazy,rev;
}all[maxn<<2];
inline void update(node &now,node &ls,node &rs)
{
    now.sum = ls.sum + rs.sum;
    for(int i = 0;i<2;++i)
    {
        now.lmax[i] = ls.lmax[i];
        if(ls.lmax[i] == ls.len)
            now.lmax[i] += rs.lmax[i];
        now.rmax[i] = rs.rmax[i];
        if(rs.rmax[i] == rs.len)
            now.rmax[i] += ls.rmax[i];
        now.maxx[i] = max(ls.maxx[i],rs.maxx[i]);
        now.maxx[i] = max(now.maxx[i],ls.rmax[i] + rs.lmax[i]);
    }
}
inline void reverse(node &now)
{
    swap(now.lmax[0], now.lmax[1]);
    swap(now.rmax[0], now.rmax[1]);
    swap(now.maxx[0], now.maxx[1]);
    now.sum = now.len - now.sum;
}
inline void push_down(const int &p)
{
    node &ls = all[p<<1],&rs = all[p<<1|1],&now = all[p];
    if(now.lazy != -1)
    {
        int v = now.lazy;
        ls.lazy = rs.lazy = v;
        ls.rev = rs.rev = 0;
        ls.lmax[v] = ls.rmax[v] = ls.maxx[v] = ls.len;
        rs.lmax[v] = rs.rmax[v] = rs.maxx[v] = rs.len;
        ls.lmax[v^1] = ls.rmax[v^1] = ls.maxx[v^1] = 0;
        rs.lmax[v^1] = rs.rmax[v^1] = rs.maxx[v^1] = 0;
        ls.sum = ls.len * v;
        rs.sum = rs.len * v;
        now.lazy = -1;
        now.rev = 0;
        return;
    }
    if(now.rev)
    {
        now.rev = 0;
        reverse(ls);
        reverse(rs);
        if(ls.lazy != -1)
            ls.lazy ^= 1;
        else
            ls.rev ^= 1;
        if(rs.lazy != -1)
            rs.lazy ^= 1;
        else
            rs.rev ^= 1;
    }
}
void build(const int &l,const int &r,const int &p)
{
    all[p].l = l,all[p].r = r,all[p].len = r - l + 1,all[p].lazy = -1;
    if(l == r)
    {
        int temp;
        read(temp);
        all[p].lmax[temp] = all[p].rmax[temp] = all[p].maxx[temp] = 1;
        all[p].sum = temp;
        return;
    }
    int mid = (l+r)>>1;
    build(l,mid,p<<1);
    build(mid+1,r,p<<1|1);
    update(all[p],all[p<<1],all[p<<1|1]);
}
int ll,rr,value;
void f_update(const int &p)
{
    node &now = all[p];
    push_down(p);
    if(ll <= now.l && rr >= now.r)
    {
        if(value == 2)
        {
            reverse(now);
            now.rev ^= 1;
            return;
        }
        now.sum = value*now.len;
        now.lmax[value] = now.rmax[value] = now.maxx[value] = now.len;
        now.lmax[value^1] = now.rmax[value^1] = now.maxx[value^1] = 0;
        now.lazy = value;
        return;
    }
    int mid = (now.l+now.r)>>1;
    if(ll <= mid)
        f_update(p<<1);
    if(rr > mid)
        f_update(p<<1|1);
    update(all[p],all[p<<1],all[p<<1|1]);
}
int askSum(const int &p)
{
    push_down(p);
    node &now = all[p];
    if(ll <= now.l && rr >= now.r)
        return now.sum;
    int mid = (now.l+now.r)>>1,ans = 0;
    if(ll <= mid)
        ans += askSum(p<<1);
    if(rr > mid)
        ans += askSum(p<<1|1);
    return ans;
}
node askCon(const int &p)
{
    node &now = all[p];
    if(ll <= now.l && rr >= now.r)
        return now;
    push_down(p);
    int mid = (now.l+now.r)>>1;
    if(ll > mid)
        return askCon(p<<1|1);
    if(rr <= mid)
        return askCon(p<<1);
    node ls = askCon(p<<1),rs = askCon(p<<1|1),res;
    res.l = ls.l,res.r = rs.r,res.len = res.r - res.l + 1;
    update(res,ls,rs);
    return res;
}
int main()
{
    read(n);
    read(m);
    build(1,n,1);
    int flag;
    for(int i = 1;i<=m;++i)
    {
        read(flag);
        read(ll);
        read(rr);
        ++ll,++rr;
        if(flag < 3)
            value = flag,f_update(1);
        else if(flag == 3)
            printf("%d\n",askSum(1));
        else
            printf("%d\n",askCon(1).maxx[1]);
    }
    return 0;
}