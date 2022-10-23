#include <cstdio>
#include <algorithm>
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
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e6 + 100;
int n, m, a[maxn], H[maxn], tot, ANS[maxn], maxx[maxn], f[maxn], g[maxn], uni[maxn], cnt[maxn];
struct opt
{
    int id, a, b, ff, gg;
} A[maxn];
inline bool cmp(const opt& a, const opt& b) { return a.a < b.a; }
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(a[i]), H[++tot] = a[i];
    for (int i = 1; i <= m; ++i) read(A[i].a), read(A[i].b), H[++tot] = A[i].b, A[i].id = i;
    std::sort(H + 1, H + 1 + tot), tot = std::unique(H + 1, H + 1 + tot) - H - 1;
    for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(H + 1, H + 1 + tot, a[i]) - H;
    for (int i = 1; i <= m; ++i) A[i].b = std::lower_bound(H + 1, H + 1 + tot, A[i].b) - H;
    a[n + 1] = ++tot;
    for (int p = 1; p <= n + 1; ++p)
    {
        for (int x = a[p] - 1; x; x -= x & -x) f[p] = std::max(maxx[x],f[p]);
        ++f[p];
        for (int x = a[p]; x <= tot; x += x & -x) maxx[x] = std::max(maxx[x],f[p]);
    }
    int ans = f[n + 1] - 1;
    for (int i = 1; i <= tot; ++i) maxx[i] = 0;
    for(int p = n;p;--p)
    {
        for (int x = tot - (a[p] + 1) + 1; x; x -= x & -x) g[p] = std::max(g[p], maxx[x]);
        ++g[p];
        for (int x = tot - a[p] + 1; x <= tot; x += x & -x) maxx[x] = std::max(maxx[x], g[p]);
    }
    std::sort(A + 1, A + 1 + m, cmp);
    for (int i = 1; i <= tot; ++i) maxx[i] = 0;
    for (int i = 1, p = 0; i <= m; ++i)
    {
        while (p + 1 < A[i].a)
            for (int x = a[++p]; x <= tot; x += x & -x) maxx[x] = std::max(maxx[x], f[p]);
        for (int x = A[i].b - 1; x; x -= x & -x) A[i].ff = std::max(A[i].ff, maxx[x]);
        ++A[i].ff;
    }
    for (int i = 1; i <= tot; ++i) maxx[i] = 0;
    for (int i = m, p = n; i; --i)
    {
        while(p > A[i].a)
        {
            for (int x = tot - a[p] + 1; x <= tot; x += x & -x) maxx[x] = std::max(maxx[x], g[p]);
            --p;
        }
        for (int x = tot - (A[i].b + 1) + 1; x; x -= x & -x) A[i].gg = std::max(A[i].gg, maxx[x]);
        ++A[i].gg;
    }
    for (int i = 1; i <= n; ++i) if (f[i] + g[i] - 1 == ans) cnt[f[i]]++;
    for (int i = 1; i <= n; ++i) if (f[i] + g[i] - 1 == ans && cnt[f[i]] == 1) uni[i] = 1;
    for (int i = 1; i <= m; ++i) 
    {
        ANS[A[i].id] = A[i].ff + A[i].gg - 1;
        if (uni[A[i].a]) ANS[A[i].id] = std::max(ANS[A[i].id], ans - 1); 
        else ANS[A[i].id] = std::max(ANS[A[i].id],ans);
    }
    for (int i = 1; i <= m; ++i) printf("%d\n", ANS[i]);
    return 0;
}
