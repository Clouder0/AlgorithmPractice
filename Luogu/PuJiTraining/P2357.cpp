#include <cstdio>
using namespace std;
template<typename T>
inline void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 2e5 + 10;
int n,m;
long long tag[maxn<<2],sum[maxn<<2];
inline void push_up(const int &p)
{
    sum[p] = sum[p<<1] + sum[p<<1|1];
}
inline void push_down(const int &l,const int &r,const int &p)
{
    if(!tag[p])
        return;
    int mid = l + r >> 1;
    sum[p<<1] += (mid - l + 1) * tag[p];
    sum[p<<1|1] += (r - mid) * tag[p];
    tag[p<<1] += tag[p];
    tag[p<<1|1] += tag[p];
    tag[p] = 0;
}
void build(int l,int r,int p)
{
    if(l == r)
    {
        read(sum[p]);
        return;
    }
    int mid = l + r >> 1;
    build(l,mid,p<<1);
    build(mid + 1,r,p<<1|1);
    push_up(p);
}
int ll,rr;
long long k;
void modify(int l,int r,int p)
{
    if(ll <= l && rr >= r)
    {
        sum[p] += (r - l + 1) * k;
        tag[p] += k;
        return;
    }
    int mid = l + r >> 1;
    push_down(l,r,p);
    if(ll <= mid)
        modify(l,mid,p<<1);
    if(rr > mid)
        modify(mid + 1,r,p<<1|1);
    push_up(p);
}
long long ask(int l,int r,int p)
{
    if(ll <= l && rr >= r)
        return sum[p];
    push_down(l,r,p);
    int mid = l + r >> 1;
    long long ans = 0;
    if(ll <= mid)
        ans += ask(l,mid,p<<1);
    if(rr > mid)
        ans += ask(mid + 1,r,p<<1|1);
    return ans;
}
int main()
{
    read(n);
    read(m);
    build(1,n,1);
    int t;
    while(m--)
    {
        read(t);
        if(t == 1)
        {
            read(ll);
            read(rr);
            read(k);
            modify(1,n,1);
        }
        else if(t == 2)
        {
            read(k);
            ll = rr = 1;
            modify(1,n,1);
        }
        else if(t == 3)
        {
            read(k);
            k *= -1;
            ll = rr = 1;
            modify(1,n,1);
        }
        else if(t == 4)
        {
            read(ll);
            read(rr);
            printf("%lld\n",ask(1,n,1));
        }
        else
        {
            ll = rr = 1;
            printf("%lld\n",ask(1,n,1));
        }
    }
    return 0;
}