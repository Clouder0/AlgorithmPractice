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
const int maxn = 1e5 + 100;
namespace SegTree
{
#define ls (p << 1)
#define rs (p << 1 | 1)
struct node
{
    int l, r, len;
    int sum;
    int lmax[2], rmax[2], maxx[2];
    int settag, revtag;
} A[maxn << 2];
int a[maxn];
void pushup(node& now, node& lson, node& rson)
{
    now.sum = lson.sum + rson.sum;
    for (int i = 0; i < 2; ++i)
    {
        now.lmax[i] = lson.lmax[i];
        if (lson.lmax[i] == lson.len) now.lmax[i] += rson.lmax[i];
        now.rmax[i] = rson.rmax[i];
        if (rson.rmax[i] == rson.len) now.rmax[i] += lson.rmax[i];
        now.maxx[i] = std::max(lson.maxx[i], std::max(rson.maxx[i], rson.lmax[i] + lson.rmax[i]));
    }
}
void pushdown(node& now, node& lson, node& rson)
{
    if (now.settag != -1)
    {
        lson.settag = rson.settag = now.settag;
        lson.revtag = rson.revtag = 0;
        lson.sum = lson.settag * lson.len;
        rson.sum = rson.settag * rson.len;
        lson.lmax[0] = lson.rmax[0] = lson.maxx[0] = lson.settag ? 0 : lson.len;
        lson.lmax[1] = lson.rmax[1] = lson.maxx[1] = lson.settag ? lson.len : 0;
        rson.lmax[0] = rson.rmax[0] = rson.maxx[0] = rson.settag ? 0 : rson.len;
        rson.lmax[1] = rson.rmax[1] = rson.maxx[1] = rson.settag ? rson.len : 0;
        now.settag = -1;
    }
    if (now.revtag)
    {
        lson.revtag ^= 1;
        rson.revtag ^= 1;
        lson.sum = lson.len - lson.sum;
        rson.sum = rson.len - rson.sum;
        std::swap(lson.lmax[0], lson.lmax[1]);
        std::swap(lson.rmax[0], lson.rmax[1]);
        std::swap(lson.maxx[0], lson.maxx[1]);
        std::swap(rson.lmax[0], rson.lmax[1]);
        std::swap(rson.rmax[0], rson.rmax[1]);
        std::swap(rson.maxx[0], rson.maxx[1]);
        now.revtag = 0;
    }
}
void build(int l, int r, int p)
{
    A[p].l = l, A[p].r = r, A[p].len = r - l + 1;
    A[p].settag = -1, A[p].revtag = 0;
    if (l == r)
    {
        int k = a[l];
        A[p].sum = k;
        A[p].lmax[k] = A[p].rmax[k] = A[p].maxx[k] = 1;
        A[p].lmax[k ^ 1] = A[p].rmax[k ^ 1] = A[p].maxx[k ^ 1] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, ls), build(mid + 1, r, rs);
    pushup(A[p], A[ls], A[rs]);
}
void seg_set(int p, int ll, int rr, int k)
{
    if (A[p].l >= ll && A[p].r <= rr)
    {
        A[p].revtag = 0, A[p].settag = k;
        A[p].sum = A[p].len * k;
        A[p].lmax[k] = A[p].rmax[k] = A[p].maxx[k] = A[p].len;
        A[p].lmax[k ^ 1] = A[p].rmax[k ^ 1] = A[p].maxx[k ^ 1] = 0;
        return;
    }
    int mid = (A[p].l + A[p].r) >> 1;
    pushdown(A[p], A[ls], A[rs]);
    if (ll <= mid) seg_set(ls, ll, rr, k);
    if (rr > mid) seg_set(rs, ll, rr, k);
    pushup(A[p], A[ls], A[rs]);
}
void reverse(int p, int ll, int rr)
{
    if (A[p].l >= ll && A[p].r <= rr)
    {
        A[p].revtag ^= 1;
        A[p].sum = A[p].len - A[p].sum;
        std::swap(A[p].lmax[0], A[p].lmax[1]);
        std::swap(A[p].rmax[0], A[p].rmax[1]);
        std::swap(A[p].maxx[0], A[p].maxx[1]);
        return;
    }
    int mid = (A[p].l + A[p].r) >> 1;
    pushdown(A[p], A[ls], A[rs]);
    if (ll <= mid) reverse(ls, ll, rr);
    if (rr > mid) reverse(rs, ll, rr);
    pushup(A[p], A[ls], A[rs]);
}
int ask_sum(int p, int ll, int rr)
{
    if (A[p].l >= ll && A[p].r <= rr) return A[p].sum;
    int mid = (A[p].l + A[p].r) >> 1, ans = 0;
    pushdown(A[p], A[ls], A[rs]);
    if (ll <= mid) ans += ask_sum(ls, ll, rr);
    if (rr > mid) ans += ask_sum(rs, ll, rr);
    return ans;
}
node ask_maxx(int p, int ll, int rr)
{
    if (A[p].l >= ll && A[p].r <= rr) return A[p];
    int mid = (A[p].l + A[p].r) >> 1;
    pushdown(A[p], A[ls], A[rs]);
    if (ll <= mid && rr > mid)
    {
        node res, lres = ask_maxx(ls, ll, rr), rres = ask_maxx(rs, ll, rr);
        pushup(res, lres, rres);
        return res;
    }
    else if (ll <= mid)
        return ask_maxx(ls, ll, rr);
    return ask_maxx(rs, ll, rr);
}
}  // namespace SegTree
int n, m;
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(SegTree::a[i]);
    SegTree::build(1, n, 1);
    while (m--)
    {
        int opt, l, r;
        read(opt), read(l), read(r);
        ++l, ++r;
        switch (opt)
        {
            case 0:
                SegTree::seg_set(1, l, r, 0);
                break;
            case 1:
                SegTree::seg_set(1, l, r, 1);
                break;
            case 2:
                SegTree::reverse(1, l, r);
                break;
            case 3:
                printf("%d\n", SegTree::ask_sum(1, l, r));
                break;
            case 4:
                printf("%d\n", SegTree::ask_maxx(1, l, r).maxx[1]);
                break;
        }
    }
    return 0;
}