#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    r=0;
    for(c = nc();!isdigit(c);) c = nc();
    for(;isdigit(c);c=nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 2e5 + 100;
int n,m,size;
struct node
{
    int l,r,id;
}Q[maxn];
bool cmp(const node &a,const node &b)
{
    if(a.l / size != b.l / size) return a.l < b.l;
    if((a.l / size) & 1) return a.r < b.r;
    return a.r > b.r;
}
int a[maxn],cnt[maxn],ans;
int ANS[maxn];
namespace seg
{
    int sum[maxn<<2],L[maxn<<2];
    void build(const int &l,const int &r,const int &p)
    {
        L[p] = l;
        if(l == r) return;
        int mid = l + r >> 1;
        build(l,mid,p<<1),build(mid + 1,r,p<<1|1);
    }
    void add(const int &l,const int &r,const int &p,const int &pos,const int &k)
    {
        sum[p] += k;
        if(sum[p] == 0) L[p] = l;
        else L[p] = n + 1;
        if(l == r) return;
        int mid = l + r >> 1;
        if(pos <= mid) add(l,mid,p<<1,pos,k);
        else add(mid + 1,r,p<<1|1,pos,k);
        L[p] = std::min(L[p<<1],L[p<<1|1]);
    }
}
bool flag;
inline void add(int x)
{
    if(x > n) return;
    cnt[x]++;
    if(flag) seg::add(1,n+1,1,x+1,1);
    else if(ans == x) for(;cnt[ans] > 0 && ans <= n;++ans);
}
inline void del(int x)
{
    if(x > n) return;
    if(flag) seg::add(1,n+1,1,x+1,-1);
    else if(--cnt[x] == 0) ans = std::min(ans,x);
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(a[i]);
    int times = 0;
    for(int i = 1;i<=m;++i) read(Q[i].l),read(Q[i].r),Q[i].id = i,times += (Q[i].r == 200000);
    if(times > 10000) flag = 1;
    size = n / std::pow(m,0.5);
    std::sort(Q + 1,Q + 1 + m,cmp);
    if(flag) seg::build(1, n + 1, 1);
    int l = 1, r = 0;
    for(int i = 1;i<=m;++i)
    {
        while(l > Q[i].l) add(a[--l]);
        while(r < Q[i].r) add(a[++r]);
        while(l < Q[i].l) del(a[l++]);
        while(r > Q[i].r) del(a[r--]);
        if(flag) ANS[Q[i].id] = seg::L[1] - 1;
        else ANS[Q[i].id] = ans;
    }
    for(int i = 1;i<=m;++i) printf("%d\n",ANS[i]);
    return 0;
}