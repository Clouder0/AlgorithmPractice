#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e5 + 100;
int n,m,h[maxn],st[maxn],top,pre[maxn],f[maxn];
long long sum[maxn << 2];
int tag[maxn << 2],minn[maxn << 2],minf[maxn << 2];
const int inf = 1<<29;
#define ls p<<1
#define rs p<<1|1
inline void pushup(const int &p)
{
    minn[p] = min(minn[ls],minn[rs]),minf[p] = min(minf[ls],minf[rs]);
}
inline void pushdown(const int &p)
{
    if(!tag[p]) return;
    minn[ls] = minf[ls] + tag[p], minn[rs] = minf[rs] + tag[p];
    tag[ls] = tag[rs] = tag[p], tag[p] = 0;
}
void build(int l,int r,int p)
{
    minn[p] = minf[p] = inf;
    if(l == r) return;
    int mid = l + r >> 1;
    build(l,mid,ls),build(mid + 1,r,rs);
}
int ask(int l,int r ,int p,int ll,int rr)
{
    if(l >= ll && r <= rr) return minn[p];
    int mid = l + r >> 1,ans = inf;
    pushdown(p);
    if(ll <= mid) ans = ask(l,mid,ls,ll,rr);
    if(rr > mid) ans = min(ans,ask(mid + 1,r,rs,ll,rr));
    return ans;
}
void modify(int l,int r,int p,int ll,int rr,int k)
{
    if(l >= ll && r <= rr) return (void)(minn[p] = (minf[p] + (tag[p] = k)));
    int mid = l + r >> 1;
    pushdown(p);
    if(ll <= mid) modify(l,mid,ls,ll,rr,k);
    if(rr > mid) modify(mid + 1,r,rs,ll,rr,k);
    pushup(p);
}
void update(int l,int r,int p,int pos)
{
    if(l == r) return (void)(minf[p] = f[pos-1],minn[p] = inf);
    int mid = l + r >> 1;
    pushdown(p);
    if(pos <= mid) update(l,mid,ls,pos);
    else update(mid + 1,r,rs,pos);
    pushup(p);
}
void output(int l,int r,int p)
{
    if(l == r) return (void)(printf("%d ",minn[p]));
    int mid = l + r >> 1;
    output(l,mid,ls),output(mid + 1,r,rs);
}
int main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(h[i]), sum[i] = sum[i - 1] + h[i];
    for (int i = 1; i <= n; ++i)
    {
        while(top && h[st[top]] < h[i]) --top;
        pre[i] = st[top],st[++top] = i;
    }
    build(1, n, 1);
    for (int i = 1; i <= n; ++i)
    {
        update(1,n,1,i);
        int l = 0,r = i,mid,ans = 0;
        while(l <= r)
        {
            mid = l + r >> 1;
            if (sum[i] - sum[mid] <= m) ans = mid, r = mid - 1; else l = mid + 1;
        }
        if (pre[i] < i) modify(1, n, 1, pre[i] + 1, i, h[i]);
        f[i] = ask(1, n, 1, ans + 1, i);
    }
    printf("%d\n",f[n]);
    return 0;
}