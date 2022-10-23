#include <cstdio>
#include <algorithm>
#include <set>
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
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
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
const int maxn = 110;
int T, n, k, a[maxn], maxx[maxn];
int main()
{
    read(T);
    while (T--)
    {
        read(n), read(k);
        for (int i = 0; i < k; ++i) maxx[i] = 0;
        for (int i = 1; i <= n; ++i) read(a[i]), maxx[i % k] = max(maxx[i % k], a[i]);
        long long res = 0;
        for (int i = 0; i < k; ++i) res += maxx[i];
        std::printf("%lld\n", res);
    }
    return 0;
}