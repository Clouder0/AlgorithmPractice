#include <algorithm>
#include <cstdio>
#include <ctype.h>

const int bufSize = 1e6;
#define DEBUG
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
const int maxn = 5e5 + 100;
int n, k;
struct node
{
    int l, r, num;
} A[maxn], B[maxn];
bool cmp(const node& a, const node& b)
{
    if (a.num == b.num) return a.l < b.l;
    return a.num > b.num;
}
int sum[maxn << 2], tag[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
inline void pushdown(const int& l, const int& r, const int& p)
{
    if (!tag[p]) return;
    int mid = l + r >> 1;
    sum[ls] = mid - l + 1;
    sum[rs] = r - mid;
    tag[ls] = tag[rs] = 1;
    tag[p] = 0;
}
void build(const int& l, const int& r, const int& p)
{
    sum[p] = tag[p] = 0;
    if (l == r) return;
    int mid = l + r >> 1;
    build(l, mid, ls), build(mid + 1, r, rs);
}
void modify(const int& l, const int& r, const int& p, const int& ll, const int& rr)
{
    if (ll > rr || ll == 0) return;
    if (l >= ll && r <= rr)
    {
        sum[p] = r - l + 1;
        tag[p] = 1;
        return;
    }
    pushdown(l, r, p);
    int mid = l + r >> 1;
    if (ll <= mid) modify(l, mid, ls, ll, rr);
    if (rr > mid) modify(mid + 1, r, rs, ll, rr);
    sum[p] = sum[ls] + sum[rs];
}
int ask(const int& l, const int& r, const int& p, const int& ll, const int& rr)
{
    if (ll == 0 || rr == 0 || ll > rr) return 0;
    if (l >= ll && r <= rr) return sum[p];
    int mid = l + r >> 1, ans = 0;
    pushdown(l, r, p);
    if (ll <= mid) ans = ask(l, mid, ls, ll, rr);
    if (rr > mid) ans += ask(mid + 1, r, rs, ll, rr);
    return ans;
}
inline bool check(int x)
{
    build(1, n, 1);
    for (int i = 1; i <= x; ++i) B[i] = A[i];
    std::sort(B + 1, B + 1 + x, cmp);
    B[x + 1].num = -1;
    int ll = 0, rr = 0, mr = 0, ml = n;
    for (int i = 1; i <= x + 1; ++i)
    {
        if (B[i].num == B[i - 1].num) ll = std::max(ll, B[i].l), rr = std::min(rr, B[i].r), ml = std::min(ml, B[i].l), mr = std::max(mr, B[i].r);
        else
        {
            if (ll > rr) return true;
            if (ask(1, n, 1, ll, rr) == rr - ll + 1) return true;
            modify(1, n, 1, ml, mr);
            ml = ll = B[i].l, rr = mr = B[i].r;
        }
    }
    return false;
}
int main()
{
    read(n), read(k);
    for (int i = 1; i <= k; ++i) read(A[i].l), read(A[i].r), read(A[i].num);
    int l = 1, r = k, mid, ans = k + 1;
    B[0].num = -1;
    while (l <= r)
    {
        mid = l + r >> 1;
        if (check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}