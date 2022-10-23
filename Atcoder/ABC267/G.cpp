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
const int maxn = 5100;
const int mod = 998244353;
int n, k, f[maxn], a[maxn];
inline int mul(const int& a, const int& b)
{
    return (1ll * a * b) % mod;
}
inline int add(const int& a, const int& b)
{
    int ret = a + b;
    return ret >= mod ? ret - mod : ret;
}
int main()
{
    read(n), read(k);
    for (int i = 1; i <= n; ++i) read(a[i]);
    std::sort(a + 1, a + 1 + n);
    f[1] = 1;
    int s = 0;
    for (int i = 2; i <= n; ++i)
    {
        s = (a[i] == a[i - 1]) ? s + 1 : 0;
        for (int t = i; t; --t)
            f[t] = add(mul(t - s, f[t]), mul(i + 1 - t + s, f[t - 1]));
    }
    printf("%d\n", f[n - k]);
    return 0;
}