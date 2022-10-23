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
const int maxn = 3e5 + 10;
int n,m;
int a[maxn],hash[maxn];
int ls[maxn<<5],rs[maxn<<5],sum[maxn<<5],root[maxn];
int cnt;
inline void push_up(const int &p)
{
    sum[p] = sum[ls[p]] + sum[rs[p]];
}
inline void build(int l,int r,int p)
{
    if(l == r)
        return;
    int mid = l + r >> 1;
    ls[p] = ++cnt;
    rs[p] = ++cnt;
    build(l,mid,ls[p]);
    build(mid + 1,r,rs[p]);
}
int tar;
int add(int l,int r,int p)
{
    int o = ++cnt;
    ls[o] = ls[p],rs[o] = rs[p],sum[o] = sum[p] + 1;
    if(l == r)
        return o;
    int mid = l + r >> 1;
    if(tar <= mid)
        ls[o] = add(l,mid,ls[o]);
    else
        rs[o] = add(mid + 1,r,rs[o]);
    push_up(o);
    return o;
}
int ask(int l,int r,int p,int q)
{
    if(l == r)
        return l;
    int mid = l + r >> 1;
    int lsum = sum[ls[p]] - sum[ls[q]];
    if(lsum >= tar)
        return ask(l,mid,ls[p],ls[q]);
    else
    {
        tar -= lsum;
        return ask(mid + 1,r,rs[p],rs[q]);
    }
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
        read(a[i]),hash[i] = a[i];
    sort(hash+1,hash+1+n);
    int num = unique(hash+1,hash+1+n) - hash - 1;
    for(int i = 1;i<=n;++i)
        a[i] = lower_bound(hash + 1,hash + 1 + num,a[i]) - hash;
    root[0] = 1;
    build(1,n,root[0]);
    for(int i = 1;i<=n;++i)
        tar = a[i],root[i] = add(1,num,root[i - 1]);
    int x,y,z;
    while(m--)
    {
        read(x);
        read(y);
        read(z);
        tar = z;
        int kkk = ask(1,num,root[y],root[x-1]);
        printf("%d\n",hash[kkk]);
    }
    return 0;
}