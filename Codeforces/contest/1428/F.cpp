#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
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
    for (; !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) *s++ = c;
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
const int maxn = 5e5 + 100;
int n, f[maxn];
char s[maxn];
int main()
{
    read(n), read(s + 1);
    long long now = 0, res = 0;
    for (int i = 0; i <= n; ++i) f[i] = n + 1;
    for (int l = n, len = 0; l; --l)
    {
        if (s[l] == '1') now += f[++len] - l;
        else while (len) f[len] = l + len, --len;
        res += now;
    }
    printf("%lld\n",res);
    return 0;
}