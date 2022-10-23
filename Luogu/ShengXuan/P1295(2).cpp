#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;
inline char nc()
{
    return getchar();
}
template<typename T>
inline T read(T &r)
{
    static char c;
    r = 0;
    for(c = nc();!isdigit(c);c=nc());
    for(;isdigit(c);c=nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 1e5 + 100;
int n, m, h[maxn];
long long sum[maxn];
int f[maxn], minn[maxn << 2], maxx[maxn << 2], tag[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
inline void pushup(const int& p) { minn[p] = min(minn[ls], minn[rs]); }
inline void pushdown(const int &p)
{
    if(!tag[p]) return;
    minn[ls] += max(maxx[ls], tag[p]) - maxx[ls], maxx[ls] = max(maxx[ls], tag[p]);
    minn[rs] += max(maxx[rs], tag[p]) - maxx[rs], maxx[rs] = max(maxx[rs], tag[p]);
    tag[ls] = max(tag[ls], tag[p]), tag[rs] = max(tag[rs], tag[p]), tag[p] = 0;
}
void modify(int l, int r, int p, int ll, int rr, int k)
{
    if (l >= ll && r <= rr) return (void)(minn[p] += max(maxx[p], k) - maxx[p], maxx[p] = max(maxx[p], k));
    pushdown(p);
    int mid = l + r >> 1;
    if(ll <= mid) modify(l,mid,ls,ll,rr,k);
    if(rr > mid) modify(mid + 1,r,rs,ll,rr,k);
    pushup(p);
}
void update(int l,int r,int p,int pos, int k)
{
    if(l == r) return (void)(minn[pos] += k);
    pushdown(p);
    int mid = l + r >> 1;
    if(pos <= mid) update(l,mid,ls,pos,k);
    else update(mid + 1,r,rs,pos,k);
    pushup(p);
}
int ask(int l, int r,int p,int ll,int rr)
{
    if(l >= ll && r <= rr) return minn[p];
    pushdown(p);
    int mid = l + r >> 1,ans = 1<<30;
    if(ll <= mid) ans = ask(l,mid,ls,ll,rr);
    if(rr > mid) ans = min(ans,ask(mid + 1,r,rs,ll,rr));
    return ans;
}
int main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(h[i]),sum[i] = sum[i-1] + h[i];
    f[1] = h[1], update(1, n, 1, 1, f[1]);
    for (int i = 2; i <= n; ++i)
    {
        int l = 1, r = i - 1,mid,ans = 1;
        modify(1,n,1,l,r,h[i]);
        while(l <= r)
        {
            mid = l + r >> 1;
            if(sum[i] - sum[mid] >= m) ans = mid,r = mid - 1;
            else l = mid + 1;
        }
        f[i] = ask(1,n,1,l,ans),update(1,n,1,i,f[i]);
    }
    printf("%d\n",f[n]);
    return 0;
}