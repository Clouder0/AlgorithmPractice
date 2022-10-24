#include <algorithm>
#include <cstdio>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e5 + 10;

// Segment Add/Query
namespace SegTree
{
#define ls p << 1
#define rs p << 1 | 1
long long a[maxn], sum[maxn << 2], addtag[maxn << 2];
inline void pushup(int p)
{
    sum[p] = sum[ls] + sum[rs];
}
inline void pushdown(int l, int r, int p)
{
    if(addtag[p] == 0) return;
    int mid = (l + r) >> 1;
    sum[ls] += 1ll * (mid - l + 1) * addtag[p];
    sum[rs] += 1ll * (r - mid) * addtag[p];
    addtag[ls] += addtag[p];
    addtag[rs] += addtag[p];
    addtag[p] = 0;
}
void build(int l, int r, int p)
{
    if (l == r) return (void)(sum[p] = a[l]);
    int mid = (l + r) >> 1;
    build(l, mid, ls);
    build(mid + 1, r, rs);
    pushup(p);
}
void seg_add(int l, int r, int p, int ll, int rr, int k)
{
    if (l >= ll && r <= rr)
    {
        sum[p] += 1ll * (r - l + 1) * k;
        addtag[p] += k;
        return;
    }
    pushdown(l, r, p);
    int mid = (l + r) >> 1;
    if (ll <= mid) seg_add(l, mid, ls, ll, rr, k);
    if (rr > mid) seg_add(mid + 1, r, rs, ll, rr, k);
    pushup(p);
}
long long seg_ask(int l,int r,int p,int ll,int rr)
{
    if(l >= ll && r <= rr) return sum[p];
    int mid = (l + r) >> 1;
    pushdown(l, r, p);
    if (ll <= mid && rr > mid) return seg_ask(l, mid, ls, ll, rr) + seg_ask(mid + 1, r, rs, ll, rr);
    if (ll <= mid) return seg_ask(l, mid, ls, ll, rr);
    return seg_ask(mid + 1, r, rs, ll, rr);
}
}  // namespace SegTree

int n, m, a[maxn];
int main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= n; ++i) SegTree::a[i] = a[i];
    SegTree::build(1, n, 1);
    while(m--)
    {
        int opt,x,y,k;
        read(opt),read(x),read(y);
        if(opt == 1)
        {
            read(k);
            SegTree::seg_add(1,n,1,x,y,k);
        }
        else
        {
            printf("%lld\n", SegTree::seg_ask(1,n,1,x,y));
        }
    }
    return 0;
}