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
int n, p[maxn], require[maxn], a[maxn];
int main()
{
    read(n);
    for (int i = 0; i < n; ++i) read(p[i]), require[i] = (i + n - p[i]) % n, a[require[i]]++;
    int sum = a[0] + a[1] + a[2];
    int maxx = sum;
    a[n] = a[0], a[n + 1] = a[1], a[n + 2] = a[2];
    for (int i = 3; i <= n+2; ++i) sum = sum + a[i] - a[i - 3], maxx = std::max(maxx, sum);
//    maxx = std::max(maxx, )
    printf("%d\n", maxx);
    return 0;
}