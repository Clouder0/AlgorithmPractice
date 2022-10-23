#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctype.h>
#define int long long
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
    r = 0;
    for (c = nc(); !isdigit(c);) c = nc();
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 1e5 + 100;
int n, m;
int H[maxn], tot, bel[maxn], L[maxn], R[maxn];
struct node
{
    int l, r, id;
} Q[maxn];
bool cmp(const node& a, const node& b)
{
    if (bel[a.l] != bel[b.l]) return a.l < b.l;
    return a.r < b.r;
}
int a[maxn];
int cnt[maxn], tcnt[maxn];
long long tans, ans, ANS[maxn];
inline void add(int x, long long& ans) { ans = std::max(ans, 1ll * ++cnt[x] * H[x]); }
inline void del(int x) { --cnt[x]; }
inline void build()
{
    int size = n / std::sqrt(m);
    int num = n / size;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = L[i] + size - 1;
        for (int j = L[i]; j <= R[i]; ++j) bel[j] = i;
    }
    if (R[num] < n)
    {
        L[num + 1] = R[num] + 1;
        R[++num] = n;
        for (int i = L[num]; i <= R[num]; ++i) bel[i] = num;
    }
}
inline void init()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(a[i]), H[++tot] = a[i];
    std::sort(H + 1, H + 1 + tot), tot = std::unique(H + 1, H + 1 + tot) - H - 1;
    for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(H + 1, H + 1 + tot, a[i]) - H;
    build();
    for (int i = 1; i <= m; ++i) read(Q[i].l), read(Q[i].r), Q[i].id = i;
    std::sort(Q + 1, Q + 1 + m, cmp);
}
signed main()
{
    init();
    int l = 1, r = 0, lastl = 1, lastblock = 0;
    for (int i = 1; i <= m; ++i)
    {
        if (bel[Q[i].l] == bel[Q[i].r])
        {
            for (int j = Q[i].l; j <= Q[i].r; ++j) ++tcnt[a[j]];
            for (int j = Q[i].l; j <= Q[i].r; ++j) ANS[Q[i].id] = std::max(ANS[Q[i].id], 1ll * tcnt[a[j]] * H[a[j]]);
            for (int j = Q[i].l; j <= Q[i].r; ++j) --tcnt[a[j]];
            continue;
        }
        if (bel[Q[i].l] != lastblock)
        {
            int p = bel[Q[i].l];
            while (r > R[p]) del(a[r--]);
            while (l < R[p] + 1) del(a[l++]);
            ans = 0;
            lastblock = p;
        }
        while (r < Q[i].r) add(a[++r], ans);
        lastl = l, tans = ans;
        while (l > Q[i].l) add(a[--l], tans);
        ANS[Q[i].id] = tans;
        while (l < lastl) del(a[l++]);
    }
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", ANS[i]);
    return 0;
}