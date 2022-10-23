#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <vector>
const int bufSize = 1e6;
using namespace std;
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
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 3e5 + 100;
int n, m, a[maxn];
struct query
{
    int l, r, id;
} Q[maxn];
int ANS[maxn];
bool cmp(const query& a, const query& b) { return a.l > b.l; }
namespace Bit
{
int sum[maxn];
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int k) { for (; x <= n; x += lowbit(x)) sum[x] += k; }
inline int ask(int x)
{
    int res = 0;
    for (; x > 0; x -= lowbit(x)) res += sum[x];
    return res;
}
inline int ask(int l, int r) { return ask(r) - ask(l - 1); }
}  // namespace Bit
namespace Seg
{
int minr[maxn << 2], minn[maxn << 2], tag[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
inline void pushdown(const int& p)
{
    if (!tag[p]) return;
    minn[ls] += tag[p], minn[rs] += tag[p];
    tag[ls] += tag[p], tag[rs] += tag[p];
    tag[p] = 0;
}
void build(int l, int r, int p)
{
    minr[p] = r, minn[p] = 1 << 30;
    if (l == r) return;
    int mid = l + r >> 1;
    build(l, mid, ls), build(mid + 1, r, rs);
}
inline void pushup(const int& p)
{
    minn[p] = std::min(minn[ls], minn[rs]);
    if (minn[rs] == minn[p]) minr[p] = minr[rs];
    else minr[p] = minr[ls];
}
void modify(int l, int r, int p, int ll, int rr, int k)
{
    if (ll > rr) return;
    if (l >= ll && r <= rr) return (void)(minn[p] += k, tag[p] += k);
    int mid = l + r >> 1;
    pushdown(p);
    if (ll <= mid) modify(l, mid, ls, ll, rr, k);
    if (rr > mid) modify(mid + 1, r, rs, ll, rr, k);
    pushup(p);
}
void set(int l, int r, int p, int pos, int k)
{
    if (l == r) return (void)(minn[p] = k);
    pushdown(p);
    int mid = l + r >> 1;
    if (pos <= mid) set(l, mid, ls, pos, k);
    else set(mid + 1, r, rs, pos, k);
    pushup(p);
}
pair<int, int> ask(int l, int r, int p, int ll, int rr)
{
    if (l >= ll && r <= rr)
    {
        if (minn[p] == 0) return make_pair(0, minr[p]);
        return make_pair(1 << 30, 0);
    }
    int mid = l + r >> 1;
    pair<int, int> res;
    res.first = 1 << 30, res.second = 0;
    pushdown(p);
    if (ll <= mid) res = ask(l, mid, p << 1, ll, rr);
    if (rr > mid)
    {
        pair<int, int> t = ask(mid + 1, r, p << 1 | 1, ll, rr);
        if (res.first >= t.first) res = t;
    }
    return res;
}
}  // namespace Seg
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(a[i]), a[i] = i - a[i];
    for (int i = 1; i <= m; ++i) read(Q[i].l), read(Q[i].r), Q[i].l++, Q[i].r = n - Q[i].r, Q[i].id = i;
    std::sort(Q + 1, Q + 1 + m, cmp);
    Seg::build(1, n, 1);
    int p = n;
    for (int i = 1; i <= m; ++i)
    {
        while (p >= Q[i].l)
        {
            if (a[p] > 0) Seg::set(1, n, 1, p, a[p]);
            else if (a[p] == 0)
            {
                Seg::modify(1, n, 1, p + 1, n, -1);
                Bit::add(p, 1);
                pair<int, int> t = Seg::ask(1, n, 1, p + 1, n);
                while (t.first != (1 << 30))
                {
                    Bit::add(t.second, 1);
                    Seg::modify(1, n, 1, t.second + 1, n, -1);
                    Seg::set(1, n, 1, t.second, n + 100);
                    t = Seg::ask(1, n, 1, p + 1, n);
                }
            }
            --p;
        }
        ANS[Q[i].id] = Bit::ask(Q[i].l, Q[i].r);
    }
    for (int i = 1; i <= m; ++i) printf("%d\n", ANS[i]);
    return 0;
}