#include <cstdio>
#include <algorithm>
template <typename T>
void read(T &r)
{
    static char c; r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 2e5 + 100;
struct Line
{
    int l, r, h, mark;
    bool operator<(const Line &b) { return this->h < b.h; }
} E[maxn << 1];
struct node
{
    int l, r, mark;
    long long len;
} a[maxn << 3];
int n;
int X[maxn << 1];
inline void pushup(const int &p)
{
    if (a[p].mark) a[p].len = X[a[p].r + 1] - X[a[p].l];
    else a[p].len = a[p << 1].len + a[p << 1 | 1].len;
}
void build(const int &l, const int &r, const int &p)
{
    a[p].l = l, a[p].r = r;
    if (l == r) return;
    int mid = l + r >> 1;
    build(l, mid, p << 1), build(mid + 1, r, p << 1 | 1);
}
void modify(const int &p, const int &ll, const int &rr, const int &k)
{
    node &now = a[p], &ls = a[p << 1], &rs = a[p << 1 | 1];
    if (X[now.l] >= ll && X[now.r + 1] <= rr)
    {
        now.mark += k;
        pushup(p);
        return;
    }
    if (ll <= X[ls.r]) modify(p << 1, ll, rr, k);
    if (rr >= X[rs.l + 1]) modify(p << 1 | 1, ll, rr, k);
    pushup(p);
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int x1, y1, x2, y2;
        read(x1), read(y1), read(x2), read(y2);
        E[(i << 1) - 1] = (Line){x1, x2, y1, 1};
        E[i << 1] = (Line){x1, x2, y2, -1};
        X[(i << 1) - 1] = x1, X[i << 1] = x2;
    }
    std::sort(E + 1, E + 1 + n * 2);
    std::sort(X + 1, X + 1 + n * 2);
    int num = std::unique(X + 1, X + 1 + n * 2) - X - 1;
    build(1, num - 1, 1);
    long long ans = 0;
    for (int i = 1; i < n * 2; ++i)
    {
        modify(1, E[i].l, E[i].r, E[i].mark);
        ans += (E[i + 1].h - E[i].h) * a[1].len;
    }
    printf("%lld\n", ans);
    return 0;
}