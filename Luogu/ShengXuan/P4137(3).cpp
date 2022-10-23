#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctype.h>
#define DEBUG
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
int n, m, L[maxn], R[maxn], pos[maxn];
int a[maxn], cnt[maxn], tempcnt[maxn], ANS[maxn];
struct node
{
    int l, r, id;
} Q[maxn];
bool cmp(const node &a, const node &b)
{
    if (pos[a.l] != pos[b.l]) return a.l < b.l;
    return a.r > b.r;
}
inline void build()
{
    int size = n / std::sqrt(m);
    int num = n / size;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1, R[i] = L[i] + size - 1;
        for (int j = L[i]; j <= R[i]; ++j) pos[j] = i;
    }
    if (R[num] < n)
    {
        L[num + 1] = R[num] + 1, R[++num] = n;
        for (int i = L[num]; i <= n; ++i) pos[i] = num;
    }
}
inline void del(int x, int &ans)
{
    if (x >= n) return;
    if (--cnt[x] == 0) ans = std::min(ans, x);
}
inline void init()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= m; ++i) read(Q[i].l), read(Q[i].r), Q[i].id = i;
    build();
    std::sort(Q + 1, Q + 1 + m, cmp);
}
int main()
{
    init();
    int l = 1, r = 0, ans = 0, lastblock = 0;
    for (int i = 1; i <= m; ++i)
    {
        if (pos[Q[i].l] == pos[Q[i].r])
        {
            for (int j = Q[i].l; j <= Q[i].r; ++j) if (a[j] < n) tempcnt[a[j]]++;
            for (; tempcnt[ANS[Q[i].id]] > 0; ++ANS[Q[i].id]);
            for (int j = Q[i].l; j <= Q[i].r; ++j) tempcnt[a[j]] = 0;
            continue;
        }
        if (pos[Q[i].l] != lastblock)
        {
            int p = pos[Q[i].l];
            l = L[p], r = n, lastblock = p;
            for (int j = 0; j <= n; ++j) cnt[j] = 0;
            for (int j = l; j <= r; ++j) if (a[j] < n) cnt[a[j]]++;
            for (ans = 0; cnt[ans] > 0; ++ans);
        }
        while (r > Q[i].r) del(a[r--], ans);
        ANS[Q[i].id] = ans;
        for (int j = l; j < Q[i].l; ++j) del(a[j], ANS[Q[i].id]);
        for (int j = l; j < Q[i].l; ++j) cnt[a[j]]++;
    }
    for (int i = 1; i <= m; ++i) printf("%d\n", ANS[i]);
    return 0;
}