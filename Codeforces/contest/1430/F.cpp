#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;
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
const int maxn = 2e3 + 100;
int n, k, l[maxn], r[maxn], a[maxn], f[maxn];
int main()
{
    read(n), read(k);
    for (int i = 1; i <= n; ++i) read(l[i]), read(r[i]), read(a[i]);
    for (int i = n; i; --i)
    {
        int need = a[i];
        if (r[i] == l[i + 1]) need += f[i + 1];
        if (1ll * (r[i] - l[i] + 1) * k < need) { puts("-1"); return 0; }
        f[i] = max(0ll, need - 1ll * (r[i] - l[i]) * k);
    }
    long long ans = 0;
    int now = k;
    for (int i = 1; i <= n; ++i)
    {
        if (now < f[i]) ans += now, now = k;
        ans += a[i];
        now = (((now - a[i]) % k) + k) % k;
    }
    printf("%lld\n", ans);
    return 0;
}