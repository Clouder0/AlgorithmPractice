#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 100;
int n,mod;
long long a[maxn<<2];
inline void pushup(const int &p)
{
    a[p] = a[p<<1] * a[p<<1|1];
    a[p] %= mod;
}
void build(const int &l,const int &r,const int &p)
{
    if(l == r)
    {
        a[p] = 1;
        return;
    }
    int mid = l + r >> 1;
    build(l,mid,p<<1);
    build(mid + 1,r,p<<1|1);
    pushup(p);
}
int target,k;
void modify(const int &l,const int &r,const int &p)
{
    if(l == r)
    {
        a[p] = k % mod;
        return;
    }
    int mid = l + r >> 1;
    if(target <= mid)
        modify(l,mid,p<<1);
    else
        modify(mid + 1,r,p<<1|1);
    pushup(p);
}
int main()
{
    int t;
    read(t);
    while(t--)
    {
        read(n);
        read(mod);
        build(1,n,1);
        for(int i = 1;i<=n;++i)
        {
            int opt,x;
            read(opt);
            read(x);
            if(opt == 1)
            {
                target = i,k = x;
                modify(1,n,1);
                printf("%lld\n",a[1]);
            }
            else
            {
                target = x,k = 1;
                modify(1,n,1);
                printf("%lld\n",a[1]);
            }
        }
    }
    return 0;
}