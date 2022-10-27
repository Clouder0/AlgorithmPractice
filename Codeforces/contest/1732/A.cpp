#include <algorithm>
#include <cstdio>
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
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc())
        ;
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
int T, a[30], n;
long long cost;
int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }
void dfs(int pos, long long now)
{
    if (now >= cost) return;
    if (pos == n + 1)
    {
        int g = a[1];
        for (int i = 2; g != 1 && i <= n; ++i) g = gcd(a[i], g);
        if (g == 1) cost = std::min(cost, now);
        return;
    }
    dfs(pos + 1, now);
    int old = a[pos];
    a[pos] = gcd(a[pos], pos);
    dfs(pos + 1, now + n - pos + 1);
    a[pos] = old;
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        cost = 1ll << 60;
        dfs(1, 0);
        printf("%lld\n", cost);
    }
    return 0;
}