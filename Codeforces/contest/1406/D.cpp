#include <algorithm>
#include <cstdio>
using namespace std;
#define int long long
const int maxn = 1e5 + 100;
int n, q;
namespace Bit
{
int a[maxn];
inline int lowbit(const int& x) { return x & -x; }
inline void add(int x, int k) { for (; x <= n; x += lowbit(x)) a[x] += k; }
inline int ask(int x)
{
    int res = 0;
    for (; x > 0; x -= lowbit(x)) res += a[x];
    return res;
}
}  // namespace Bit
int origina[maxn], originc[maxn];
namespace Seg
{
#define ls p << 1
#define rs p << 1 | 1
int maxx[maxn << 2], tag[maxn << 2];
inline void pushup(const int& p) { maxx[p] = max(maxx[ls], maxx[rs]); }
inline void pushdown(const int& p)
{
    if (!tag[p]) return;
    maxx[ls] += tag[p], maxx[rs] += tag[p];
    tag[ls] += tag[p], tag[rs] += tag[p];
    tag[p] = 0;
}
void build(int l, int r, int p)
{
    maxx[p] = -(1 << 30);
    if (l == r) return (void)(maxx[p] = origina[l] - originc[l]);
    int mid = l + r >> 1;
    build(l, mid, ls), build(mid + 1, r, rs);
    pushup(p);
}
void add(int l, int r, int p, int ll, int rr, int k)
{
    if (ll > rr) return;
    if (l >= ll && r <= rr) return (void)(maxx[p] += k, tag[p] += k);
    pushdown(p);
    int mid = l + r >> 1;
    if (ll <= mid) add(l, mid, ls, ll, rr, k);
    if (rr > mid) add(mid + 1, r, rs, ll, rr, k);
    pushup(p);
}
}  // namespace Seg
inline void output()
{
    int bottom = Seg::maxx[1] / 2, top = (Seg::maxx[1] + 1) / 2;
    int res = 1ll << 60;
    for (int c1 = bottom; c1 <= top; ++c1) res = std::min(res, max(c1, Seg::maxx[1] - c1));
    printf("%lld\n", res);
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", origina + i), Bit::add(i, origina[i]), Bit::add(i + 1, -origina[i]);
    for (int i = 2; i <= n; ++i) originc[i] = originc[i - 1] + min(0ll, origina[i] - origina[i - 1]);
    Seg::build(1, n, 1);
    output();
    scanf("%lld", &q);
    while (q--)
    {
        int l, r, x;
        scanf("%lld %lld %lld", &l, &r, &x);
        Seg::add(1, n, 1, l, r, x);
        if (l != 1)
        {
            int al1 = Bit::ask(l - 1), al2 = Bit::ask(l);
            Seg::add(1, n, 1, l, n, min(al2 - al1, 0ll) - min(x + al2 - al1, 0ll));
        }
        if (r != n)
        {
            int ar1 = Bit::ask(r), ar2 = Bit::ask(r + 1);
            Seg::add(1, n, 1, r + 1, n, min(ar2 - ar1, 0ll) - min(ar2 - ar1 - x, 0ll));
        }
        Bit::add(l, x), Bit::add(r + 1, -x);
        output();
    }
}