#include <algorithm>
#include <cstdio>
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
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc()) {}
    for (; isalpha(c); c = nc()) { *s++ = c; }
    *s = '\0';
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') { flag = -1; }
    for (; isdigit(c); c = nc()) { r = r * 10 + c - 48; }
    return r *= flag;
}
const int maxn = 210;
const int maxl = 310;
int T, n;
char s[maxn][maxl];
int a[maxn], len[maxn];
int main()
{
    read(T);
    while (T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i) { read(a[i]); }
        ++n;
        a[n + 1] = 0;
        for (int i = 1; i <= n; ++i) { len[i] = std::max(a[i - 1], a[i]) + 2; }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= len[i]; ++j) { s[i][j] = 0; }
        for (int i = 1; i <= len[1]; ++i) { s[1][i] = 'a'; }
        for (int i = 2; i <= n; ++i)
        {
            for (int j = 1; j <= a[i - 1]; ++j) { s[i][j] = s[i - 1][j]; }
            for (char j = 'a'; j <= 'z'; ++j)
                if (j != s[i - 1][a[i - 1] + 1])
                {
                    s[i][a[i - 1] + 1] = j;
                    break;
                }
            for (int j = a[i - 1] + 2; j <= len[i]; ++j) { s[i][j] = 'a'; }
            s[i][len[i] + 1] = '\0';
        }
        for (int i = 1; i <= n; ++i) { printf("%s\n", (s[i] + 1)); }
    }
    return 0;
}