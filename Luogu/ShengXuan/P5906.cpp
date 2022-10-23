#include <cstdio>
#include <algorithm>
#include <cmath>
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
inline T read(T &r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c);) c = nc();
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 2e5 + 100;
int pos[maxn], L[maxn], R[maxn];
struct node
{
    int l, r, id;
} Q[maxn];
bool cmp(const node &a, const node &b)
{
    if (pos[a.l] != pos[b.l]) return a.l < b.l;
    return a.r < b.r;
}
int n, m;
int H[maxn], tot;
int a[maxn], ANS[maxn], first[maxn], last[maxn], tempfirst[maxn], templast[maxn], ans;
inline void build()
{
    int size = n / std::sqrt(n);
    int num = n / size;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = L[i] + size - 1;
        for (int j = L[i]; j <= R[i]; ++j) pos[j] = i;
    }
    if (R[num] < n)
    {
        L[num + 1] = R[num] + 1;
        R[++num] = n;
        for (int j = L[num]; j <= R[num]; ++j) pos[j] = num;
    }
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]), H[++tot] = a[i];
    read(m);
    for (int i = 1; i <= m; ++i) read(Q[i].l), read(Q[i].r), Q[i].id = i;
    std::sort(H + 1, H + 1 + tot), tot = std::unique(H + 1, H + 1 + tot) - H - 1;
    for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(H + 1, H + 1 + tot, a[i]) - H;
    build();
    std::sort(Q + 1, Q + 1 + m, cmp);
    int l = 1, r = 0, lastblock = -1;
    for (int i = 1; i <= m; ++i)
    {
        if (pos[Q[i].l] == pos[Q[i].r])
        {
            for (int j = Q[i].l; j <= Q[i].r; ++j) tempfirst[a[j]] = 0;
            for (int j = Q[i].l; j <= Q[i].r; ++j)
            {
                if (tempfirst[a[j]]) ANS[Q[i].id] = std::max(ANS[Q[i].id], j - tempfirst[a[j]]);
                else tempfirst[a[j]] = j;
            }
            for (int j = Q[i].l; j <= Q[i].r; ++j) tempfirst[a[j]] = 0;
            continue;
        }
        if (pos[Q[i].l] != lastblock)
        {
            int p = pos[Q[i].l];
            for (int i = 1; i <= tot; ++i) first[i] = last[i] = 0;
            l = R[p] + 1, r = R[p];
            ans = 0, lastblock = p;
        }
        while (r < Q[i].r)
        {
            ++r;
            last[a[r]] = r;
            if (first[a[r]]) ans = std::max(ans, r - first[a[r]]);
            else first[a[r]] = r;
        }
        int tans = ans;
        for (int j = Q[i].l; j < l; ++j) tempfirst[a[j]] = first[a[j]], templast[a[j]] = last[a[j]];
        for (int j = l - 1; j >= Q[i].l; --j)
        {
            first[a[j]] = j;
            if (last[a[j]]) tans = std::max(tans, last[a[j]] - j);
            else last[a[j]] = j;
        }
        ANS[Q[i].id] = tans;
        for (int j = Q[i].l; j < l; ++j) first[a[j]] = tempfirst[a[j]], last[a[j]] = templast[a[j]];
    }
    for (int i = 1; i <= m; ++i) printf("%d\n", ANS[i]);
    return 0;
}