#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e5 + 1000;
struct node
{
    int l,r,len;
    long long add,mul,sum;
}a[maxn<<2];
int n,m,mod;
inline void push_up(const int &p)
{
    node &now = a[p],&ls = a[p<<1],&rs = a[p<<1|1];
    now.sum = (ls.sum + rs.sum) % mod;
}
inline void push_down(const int &p)
{
    node &now = a[p],&ls = a[p<<1],&rs = a[p<<1|1];
    if(now.mul != 1)
    {
        ls.add = (ls.add * now.mul) % mod;
        rs.add = (rs.add * now.mul) % mod;
        ls.mul = (ls.mul * now.mul) % mod;
        rs.mul = (rs.mul * now.mul) % mod;
        ls.sum = ((long long)ls.sum * now.mul) % mod;
        rs.sum = ((long long)rs.sum * now.mul) % mod;
        now.mul = 1;
    }
    if (now.add)
    {
        ls.add = (ls.add + now.add) % mod;
        rs.add = (rs.add + now.add) % mod;
        ls.sum = (ls.sum + ((long long)ls.len * now.add) % mod) % mod;
        rs.sum = (rs.sum + ((long long)rs.len * now.add) % mod) % mod;
        now.add = 0;
    }
}
void build(const int &l,const int &r,const int &p)
{
    a[p].l = l,a[p].r = r,a[p].len = r - l + 1,a[p].mul = 1,a[p].sum = a[p].add = 0;
    if(l == r)
    {
        read(a[p].sum);
        return;
    }
    int mid = (l+r) >> 1;
    build(l,mid,p<<1);
    build(mid+1,r,p<<1|1);
    push_up(p);
}
int ll,rr,k;
void add(const int &l,const int &r,const int &p)
{
    push_down(p);
    if(ll <= l && rr >= r)
    {
        a[p].sum = (a[p].sum + ((long long)a[p].len * k) % mod) % mod;
        a[p].add = (a[p].add + k) % mod;
        return;
    }
    int mid = (l+r)>>1;
    if(ll <= mid)
        add(l,mid,p<<1);
    if(rr > mid)
        add(mid+1,r,p<<1|1);
    push_up(p);
}
void multiply(const int &l,const int &r,const int &p)
{
    push_down(p);
    if(ll <= l && rr >= r)
    {
        a[p].sum = ((long long)a[p].sum * k) % mod;
        a[p].mul = (a[p].mul * k) % mod;
        return;
    }
    int mid = (l+r)>>1;
    if(ll <= mid)
        multiply(l,mid,p<<1);
    if(rr > mid)
        multiply(mid+1,r,p<<1|1);
    push_up(p);
}
int ask(const int &l,const int &r,const int &p)
{
    push_down(p);
    if(ll <= l && rr >= r)
        return a[p].sum;
    int mid = (l+r)>>1;
    int ans = 0;
    if(ll <= mid)
        ans += ask(l,mid,p<<1);
    if(rr > mid)
        ans = (ans + ask(mid+1,r,p<<1|1)) % mod;
    return ans;
}
int main()
{
    read(n);
    read(m);
    read(mod);
    build(1,n,1);
    int opt;
    while(m--)
    {
        read(opt);
        read(ll);
        read(rr);
        if(opt == 1)
            read(k),multiply(1,n,1);
        else if(opt == 2)
            read(k),add(1,n,1);
        else
            printf("%d\n",ask(1,n,1));
    }
    return 0;
}