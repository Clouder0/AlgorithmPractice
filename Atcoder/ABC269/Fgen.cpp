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
int n, m, Q;
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            for (int p = 1; p <= m; ++p)
                for (int q = p; q <= m; ++q)
                {
                    ++Q;
                    printf("%d %d %d %d\n", i, j, p, q);
                }
    printf("%d\n", Q);
    return 0;
}