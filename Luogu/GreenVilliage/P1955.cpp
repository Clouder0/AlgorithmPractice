#include <cstdio>
#include <algorithm>
#include <cctype>
const int maxn = 2e6 + 100;
const int bufSize = 1e6;
inline char nc()
{
    return getchar();
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
void read(T &r)
{
    static char c;
    for (c = nc(); !isdigit(c);) c = nc();
    for (r = 0; isdigit(c); c = nc()) r = r * 10 + c - 48;
}
int T, n, a[maxn], b[maxn], e[maxn], H[maxn], cnt;
int fa[maxn << 1];
int find(const int& x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int x, int y)
{
    x = find(x), y = find(y);
    fa[x] = y;
}
int main()
{
    read(T);
    while (T--)
    {
        read(n), cnt = 0;
        for (int i = 1; i <= n; ++i) read(a[i]), read(b[i]), read(e[i]), H[++cnt] = a[i], H[++cnt] = b[i];
        std::sort(H + 1, H + 1 + cnt), cnt = std::unique(H + 1, H + 1 + cnt) - H - 1;
        for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(H + 1, H + 1 + cnt, a[i]) - H;
        for (int i = 1; i <= n; ++i) b[i] = std::lower_bound(H + 1, H + 1 + cnt, b[i]) - H;
        for (int i = 1; i <= cnt; ++i) fa[i] = i;
        for (int i = 1; i <= n; ++i)
            if (e[i]) merge(a[i], b[i]);
        for (int i = 1; i <= n; ++i)
            if (!e[i] && find(a[i]) == find(b[i])) goto no;
        puts("YES");
        continue;
    no:
        puts("NO");
    }
    return 0;
}