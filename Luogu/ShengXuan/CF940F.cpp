#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
//#define DEBUG
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
    int l,r,t,id;
}Q[maxn];
struct change
{
    int pos,val;
}C[maxn];
int cnum,qnum;
bool cmp(const node &a,const node &b)
{
    if(a.l / size != b.l / size) return a.l < b.l;
    if(a.r / size != b.r / size) return a.r < b.r;
    if((a.r / size) & 1) return a.t < b.t;
    else return a.t > b.t;
}
int H[maxn<<1],tot,a[maxn];
int cnt[maxn],rkcnt[maxn];
int ANS[maxn];
inline void add(int x)
{
    --rkcnt[cnt[x]];
    ++rkcnt[++cnt[x]];
}
inline void del(int x)
{
    --rkcnt[cnt[x]];
    ++rkcnt[--cnt[x]];
}
inline void modify(int l,int r,int t)
{
    if(C[t].pos >= l && C[t].pos <= r)
    {
        del(a[C[t].pos]);
        add(C[t].val);
    }
    std::swap(C[t].val,a[C[t].pos]);
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(a[i]),H[++tot] = a[i];
    for(int i = 1;i<=m;++i)
    {
        int opt;
        read(opt);
        if(opt == 1) read(Q[++qnum].l),read(Q[qnum].r),Q[qnum].id = qnum,Q[qnum].t = cnum;
        else read(C[++cnum].pos),read(C[cnum].val),H[++tot] = C[cnum].val;
    }
    std::sort(H + 1,H + 1 + tot),tot = std::unique(H + 1,H + 1 + tot) - H - 1;
    for(int i = 1;i<=n;++i) a[i] = std::lower_bound(H + 1,H + 1 + tot,a[i]) - H;
    for(int i = 1;i<=cnum;++i) C[i].val = std::lower_bound(H + 1,H + 1 + tot,C[i].val) - H;
    size = std::pow(n,0.7);
    std::sort(Q + 1,Q + 1 + qnum,cmp);
    int l = 1,r = 0,t = 0;
    for(int i = 1;i<=qnum;++i)
    {
        while(l > Q[i].l) add(a[--l]);
        while(r < Q[i].r) add(a[++r]);
        while(l < Q[i].l) del(a[l++]);
        while(r > Q[i].r) del(a[r--]);
        while(t < Q[i].t) modify(Q[i].l,Q[i].r,++t);
        while(t > Q[i].t) modify(Q[i].l,Q[i].r,t--);
        for(ANS[Q[i].id] = 1;rkcnt[ANS[Q[i].id]] > 0;++ANS[Q[i].id]);
    }
    for(int i = 1;i<=qnum;++i) printf("%d\n",ANS[i]);
    return 0;
}