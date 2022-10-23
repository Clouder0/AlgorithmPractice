#include <algorithm>
#include <cstdio>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
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
const int maxn = 5e3 + 100;
int n, k, P[maxn], C[maxn];
long long sum[maxn], f[maxn];
int vis[maxn];
inline long long check(int s)
{
    for (int i = 0; i <= n; ++i) sum[i] = f[i] = -(1ll << 60), vis[i] = 0;
    sum[0] = 0;
    int u = s, i = 1;
    for (;; ++i)
    {
        u = P[u];
        sum[i] = sum[i - 1] + C[u];
        f[i] = std::max(f[i - 1], sum[i]);
        if (vis[u]) break;
        else vis[u] = i;
    }
    if (k <= i) return f[k];
    long long num = sum[i] - sum[vis[u]];
    if (num <= 0) return f[i];
    int len = i - vis[u];
    int times = (k - vis[u]) / len, pos = k - times * len;
    return f[pos] + num * times;
}
int main()
{
    read(n), read(k);
    for (int i = 1; i <= n; ++i) read(P[i]);
    for (int i = 1; i <= n; ++i) read(C[i]);
    long long ans = check(1);
    for (int i = 2; i <= n; ++i) ans = std::max(ans, check(i));
    printf("%lld\n", ans);
    return 0;
}