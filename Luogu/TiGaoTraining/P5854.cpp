#include <cstdio>
#include <cctype>
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
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 1e7 + 100;
int n, a[maxn], s[maxn], top, L[maxn], R[maxn];
long long res;
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        while (top && a[s[top]] >= a[i]) --top;
        L[i] = R[s[top]];
        if (top) R[s[top]] = i;
        s[++top] = i;
    }
    for (int i = 1; i <= n; ++i) res ^= 1ll * i * (L[i] + 1);
    printf("%lld ", res);
    res = 0;
    for (int i = 1; i <= n; ++i) res ^= 1ll * i * (R[i] + 1);
    printf("%lld\n", res);
    return 0;
}