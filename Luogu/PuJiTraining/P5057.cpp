#include <cstdio>
using namespace std;
template<typename T>
inline int read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    return r;
}
const int maxn = 1e5 + 10;
const int maxm = 5e5 + 10;
int n,m;
int num[maxn<<2],lazy[maxn<<2];
inline void push_down(int p)
{
    if(!lazy[p])
        return;
    lazy[p] = 0;
    lazy[p<<1] ^= 1;
    lazy[p<<1|1] ^= 1;
}
void build(int l,int r,int p)
{
    if(l == r)
    {
        read(num[p]);
        return;
    }
    int mid = l + r >> 1;
    build(l,mid,p<<1);
    build(mid+1,r,p<<1|1);
}
int target;
int ask(int l,int r,int p)
{
    if(l == r)
        return lazy[p]?num[l]^1:num[l];
    push_down(p);
    int mid = l + r >> 1;
    if(target <= mid)
        return ask(l,mid,p<<1);
    else
        return ask(mid+1,r,p<<1|1);
}
int ll,rr;
void modify(int l,int r,int p)
{
    if(l >= ll && r <= rr)
    {
        lazy[p] ^= 1;
        return;
    }
    int mid = l + r >> 1;
    if(ll <= mid)
        modify(l,mid,p<<1);
    if(rr > mid )
        modify(mid+1,r,p<<1|1);
}
int main()
{
    read(n);
    read(m);
    int t;
    while(m--)
    {
        read(t);
        if(t == 1)
        {
            read(ll);
            read(rr);
            modify(1,n,1);
        }
        else
        {
            read(target);
            printf("%d\n",ask(1,n,1));
        }
    }
    return 0;
}
