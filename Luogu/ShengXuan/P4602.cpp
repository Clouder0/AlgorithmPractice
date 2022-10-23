#include <algorithm>
#include <cstdio>
#include <ctype.h>
const int bufSize = 1e6;
#define int long long
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
int n, m, ans[maxn], H[maxn], tot;
struct node
{
    int val, cost, limit;
} A[maxn];
bool cmp(const node& a, const node& b) { return a.val < b.val; }
struct query
{
    int id, money, amount;
} B[maxn], q1[maxn], q2[maxn];
long long asum[maxn << 2], csum[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
inline void pushup(int p) { asum[p] = asum[ls] + asum[rs], csum[p] = csum[ls] + csum[rs]; }
void modify(int l, int r, int p, int pos, long long k)
{
    if (l == r) return (void)(asum[p] += k, csum[p] += k * H[l]);
    int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, ls, pos, k);
    else modify(mid + 1, r, rs, pos, k);
    pushup(p);
}
long long havemoney, canget;
void ask(int l, int r, int p)
{
    if (havemoney <= 0) return;
    if (csum[p] <= havemoney) return (void)(havemoney -= csum[p], canget += asum[p]);
    if (l == r) return (void)(canget += havemoney / H[l], havemoney = 0);
    int mid = l + r >> 1;
    ask(l, mid, ls), ask(mid + 1, r, rs);
}
void solve(int l, int r, int L, int R)
{
    if (L > R) return;
    if (l == r)
    {
        for (int i = L; i <= R; ++i) ans[B[i].id] = A[l].val;
        return;
    }
    int mid = l + r >> 1, cnt1 = 0, cnt2 = 0;
    //push [mid + 1,r] in
    for (int i = mid + 1; i <= r; ++i) modify(1, tot, 1, A[i].cost, A[i].limit);
    for (int i = L; i <= R; ++i)
    {
        havemoney = B[i].money, canget = 0, ask(1, tot, 1);
        if (canget >= B[i].amount) q2[++cnt2] = B[i];
        else q1[++cnt1] = B[i];
    }
    for (int i = 1; i <= cnt1; ++i) B[L + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i) B[L + cnt1 + i - 1] = q2[i];
    solve(l, mid, L, L + cnt1 - 1);
    //now cancel [mid + 1,r] to goto the right division
    for (int i = mid + 1; i <= r; ++i) modify(1, tot, 1, A[i].cost, -A[i].limit);
    solve(mid + 1, r, L + cnt1, R);
}
signed main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(A[i].val), read(A[i].cost), read(A[i].limit), H[++tot] = A[i].cost;
    for (int i = 1; i <= m; ++i) read(B[i].money), read(B[i].amount), B[i].id = i;
    std::sort(H + 1, H + 1 + tot), tot = std::unique(H + 1, H + 1 + tot) - H - 1;
    for (int i = 1; i <= n; ++i) A[i].cost = std::lower_bound(H + 1, H + 1 + tot, A[i].cost) - H;
    std::sort(A + 1, A + 1 + n, cmp);
    solve(0, n, 1, m);
    for (int i = 1; i <= m; ++i) if (ans[i]) printf("%lld\n", ans[i]); else puts("-1");
    return 0;
}