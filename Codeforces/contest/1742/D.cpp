#include <cstdio>
#include <algorithm>
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
int T, n, a[maxn], maxx[maxn];
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i) read(a[i]);
        for (int i = 1; i <= 1000; ++i) maxx[i] = 0;
        int res = -1;
        for (int i = 1; i <= n; ++i)
            maxx[a[i]] = i;
        for(int i = 1;i<=1000;++i)
        {
            if(!maxx[i]) continue;
            for (int j = 1; j <= 1000; ++j)
                if (maxx[j] && gcd(i, j) == 1) res = std::max(res, maxx[i] + maxx[j]);
        }
        printf("%d\n", res);
    }
    return 0;
}