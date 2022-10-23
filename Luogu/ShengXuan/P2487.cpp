#include <cstdio>
#include <algorithm>
using namespace std;
template <typename T>
void read(T &r)
{
    static char c; r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 5e4 + 100;
struct node
{
    int t, v, h;
} A[maxn];
bool cmpv(const node &a, const node &b)
{
    if (a.v == b.v && a.h == b.h) return a.t < b.t;
    if (a.v == b.v) return a.h > b.h;
    return a.v > b.v;
}
bool cmph(const node &a, const node &b)
{
    if (a.h == b.h) return a.t < b.t;
    return a.h > b.h;
}
int n;
int f1[maxn], f2[maxn];
double g1[maxn], g2[maxn];
namespace Seg
{
    int maxx[maxn << 2];
    double num[maxn << 2];
    void clear(int l, int r, int p)
    {
        if (maxx[p] == 0) return;
        maxx[p] = 0;
        if (l == r) return;
        int mid = l + r >> 1;
        clear(l, mid, p << 1), clear(mid + 1, r, p << 1 | 1);
    }
    void modify(int l, int r, int p, int x, int k, double vnum)
    {
        if (l == r)
        {
            if (maxx[p] < k) maxx[p] = k, num[p] = 0;
            if (maxx[p] == k) num[p] += vnum;
            return;
        }
        int mid = l + r >> 1;
        if (x <= mid) modify(l, mid, p << 1, x, k, vnum);
        else modify(mid + 1, r, p << 1 | 1, x, k, vnum);
        maxx[p] = max(maxx[p << 1], maxx[p << 1 | 1]);
        num[p] = 0;
        if (maxx[p] == maxx[p << 1]) num[p] += num[p << 1];
        if (maxx[p] == maxx[p << 1 | 1]) num[p] += num[p << 1 | 1];
    }
    int ask(int l, int r, int p, int ll, int rr, double &anum)
    {
        if (ll <= l && rr >= r)
        {
            anum = num[p];
            return maxx[p];
        }
        int mid = l + r >> 1;
        int lans(0), rans(0);
        double lnum = 0.0, rnum = 0.0;
        if (ll <= mid) lans = ask(l, mid, p << 1, ll, rr, lnum);
        if (rr > mid) rans = ask(mid + 1, r, p << 1 | 1, ll, rr, rnum);
        int res = max(lans, rans);
        if (ll <= mid && res == lans) anum += lnum;
        if (rr > mid && res == rans) anum += rnum;
        return res;
    }
} // namespace Seg
void cdq(int l, int r)
{
    if (l == r) return;
    int mid = l + r >> 1;
    cdq(l, mid);
    sort(A + l, A + mid + 1, cmph);
    sort(A + mid + 1, A + r + 1, cmph);
    Seg::clear(1, n, 1);
    for (int i = l, j = mid + 1; j <= r; ++j)
    {
        while (i <= mid && A[i].h >= A[j].h)
        {
            Seg::modify(1, n, 1, A[i].t, f1[A[i].t], g1[A[i].t]);
            ++i;
        }
        double ans = 0;
        int t = Seg::ask(1, n, 1, 1, A[j].t, ans);
        if (!t) continue;
        if (f1[A[j].t] < t + 1) f1[A[j].t] = t + 1, g1[A[j].t] = 0;
        if (f1[A[j].t] == t + 1) g1[A[j].t] += ans;
    }
    sort(A + mid + 1, A + r + 1, cmpv);
    cdq(mid + 1, r);
}
void cdq2(int l, int r)
{
    if (l == r) return;
    int mid = l + r >> 1;
    cdq2(l, mid);
    sort(A + l, A + mid + 1, cmph);
    sort(A + mid + 1, A + r + 1, cmph);
    Seg::clear(1, n, 1);
    for (int i = l, j = mid + 1; j <= r; ++j)
    {
        while (i <= mid && A[i].h >= A[j].h)
        {
            Seg::modify(1, n, 1, A[i].t, f2[A[i].t], g2[A[i].t]);
            ++i;
        }
        double ans = 0;
        int t = Seg::ask(1, n, 1, 1, A[j].t, ans);
        if (!t) continue;
        if (f2[A[j].t] < t + 1) f2[A[j].t] = t + 1, g2[A[j].t] = 0;
        if (f2[A[j].t] == t + 1) g2[A[j].t] += ans;
    }
    sort(A + mid + 1, A + r + 1, cmpv);
    cdq2(mid + 1, r);
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) A[i].t = i, read(A[i].h), read(A[i].v), f1[i] = f2[i] = 1, g1[i] = g2[i] = 1;
    sort(A + 1, A + 1 + n, cmpv);
    cdq(1, n);
    int maxL = 0;
    double fsum = 0;
    for (int i = 1; i <= n; ++i) maxL = max(maxL, f1[i]);
    for (int i = 1; i <= n; ++i) if (f1[i] == maxL) fsum += g1[i];
    printf("%d\n", maxL);
    for (int i = 1; i <= n; ++i) A[i].t = n - A[i].t + 1, A[i].h = -A[i].h, A[i].v = -A[i].v;
    sort(A + 1, A + 1 + n, cmpv);
    cdq2(1, n);
    for (int i = 1; i <= n; ++i)
    {
        if (f1[i] + f2[n - i + 1] - 1 != maxL) printf("0.0 ");
        else printf("%.5f ", g1[i] * g2[n - i + 1] / fsum);
    }
    return 0;
}