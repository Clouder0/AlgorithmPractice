#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 1e5 + 100;
int n,m;
int a[maxn];
int sum[maxn<<2],tag[maxn<<2];
inline void pushup(const int &p)
{
    sum[p] = sum[p<<1] + sum[p<<1|1];
}
inline void pushdown(const int &l,const int &r,const int &p)
{
    if(!tag[p])
        return;
    int mid = l + r >> 1;
    sum[p<<1] += tag[p] * (mid - l + 1);
    sum[p<<1|1] += tag[p] * (r - mid);
    tag[p<<1] += tag[p];
    tag[p<<1|1] += tag[p];
    tag[p] = 0;
}
int ll,rr,k;
void modify(const int &l,const int &r,const int &p)
{
    if(ll <= l && rr >= r)
    {
        sum[p] += k * (r - l + 1);
        tag[p] += k;
        return;
    }
    pushdown(l,r,p);
    int mid = l + r >> 1;
    if(ll <= mid)
        modify(l,mid,p<<1);
    if(rr > mid)
        modify(mid + 1,r,p<<1|1);
    pushup(p);
}
int ask(const int &l,const int &r,const int &p)
{
    if(ll <= l && rr >= r)
        return sum[p];
    pushdown(l,r,p);
    int mid = l + r >> 1;
    int ans = 0;
    if(ll <= mid)
        ans = ask(l,mid,p<<1);
    if(rr > mid)
        ans += ask(mid + 1,r,p<<1|1);
    return ans;
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
        read(a[i]);
    while(m--)
    {
        int opt,l,r,K,D,p;
        read(opt);
        if(opt == 1)
        {
            read(l);
            read(r);
            read(K);
            read(D);
            ll = rr = l, k = K;
            modify(1, n, 1);
            if(r > l)
            {
                ll = l + 1, rr = r, k = D;
                modify(1, n, 1);
            }
            k = -(K + (r - l) * D), ll = rr = r + 1;
            modify(1, n, 1);
        }
        else
        {
            read(p);
            ll = 1, rr = p;
            printf("%d\n", a[p] + ask(1, n, 1));
        }
    }
    return 0;
}