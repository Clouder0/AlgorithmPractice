#include <cstdio>
#include <algorithm>
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
}
template <typename T>
inline T max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
const int maxn = 1e6 + 100;
int n, m;
namespace Bit
{
    int val[maxn], vis[maxn], time;
    inline void clear() { ++time; }
    inline int lowbit(int x) { return x & (-x); }
    inline void check(int x)
    {
        if (vis[x] != time)
            vis[x] = time, val[x] = 0;
    }
    inline void add(int x, int k)
    {
        for (; x <= 4 * n; x += lowbit(x))
            check(x), val[x] = max(val[x], k);
    }
    inline int ask(int x)
    {
        int res = 0;
        for (; x; x -= lowbit(x))
            check(x), res = max(res, val[x]);
        return res;
    }
    inline void del(int x)
    {
        for (; x <= 4 * n; x += lowbit(x))
            val[x] = 0;
    }
} // namespace Bit
int f[maxn];
struct node
{
    int pos, maxx, minn, val;
} A[maxn], B[maxn];
bool cmp_pos(const node &a, const node &b) { return a.pos < b.pos; }
bool cmp_max(const node &a, const node &b) { return a.maxx < b.maxx; }
bool cmp_val(const node &a, const node &b) { return a.val < b.val; }
void cdq(int l, int r)
{
    if (l == r)
    {
        f[r] = max(f[r], 1);
        return;
    }
    int mid = l + r >> 1;
    cdq(l, mid);
    int p = l, q = mid + 1;
    std::sort(A + l, A + mid + 1, cmp_max);
    std::sort(A + mid + 1, A + r + 1, cmp_val);
    Bit::clear();
    for (; q <= r; ++q)
    {
        while (p <= mid && A[p].maxx <= A[q].val)
            Bit::add(A[p].val, f[A[p].pos]), ++p;
        f[A[q].pos] = max(f[A[q].pos], Bit::ask(A[q].minn) + 1);
    }
    std::sort(A + l, A + r + 1, cmp_pos);
    cdq(mid + 1, r);
}
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i)
        A[i].pos = i, read(A[i].val), A[i].minn = A[i].maxx = A[i].val;
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x), read(y);
        A[x].maxx = max(A[x].maxx, y), A[x].minn = min(A[x].minn, y);
    }
    cdq(1, n);
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans = max(ans, f[i]);
    printf("%d", ans);
    return 0;
}