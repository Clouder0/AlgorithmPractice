#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
#define int long long
#define DEBUG
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
const int maxn = 2e5 + 100;
int n, a[maxn], maxx[maxn], f[maxn];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    int res = 0;
    for (int sum = 2; sum <= 200; ++sum)
    {
        for (int i = 0; i <= 200; ++i) maxx[i] = -(1ll << 60);
        for (int i = 1; i <= n; ++i) f[i] = 0;
        maxx[a[1]] = 0;
        for (int i = 2; i <= n; ++i)
        {
            f[i] = f[i - 1];
            if (a[i] >= sum)
                continue;
            f[i] = max(maxx[sum - a[i]] + 2, f[i - 1]);
            maxx[a[i]] = max(maxx[a[i]], f[i - 1]);
            res = max(res, f[i]);
        }
    }
    printf("%lld\n", res);
    return 0;
}
