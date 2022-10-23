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
int T, n, x, y, wins;
int main()
{
    read(T);
    while (T--)
    {
        read(n), read(x), read(y);
        if (x < y) std::swap(x, y);
        if (x == 0 && y == 0)
        {
            puts("-1");
            goto end;
        }
        if (y == 0)
        {
            if ((n - 1) % x != 0) goto fail;
            wins = (n - 1) / x;
            int now = 2, winner = 1;
            for (int i = 1; i <= wins; winner = now, ++i)
                for (int j = 1; j <= x; ++j) printf("%d ", winner), ++now;
            puts("");
            goto end;
        }
    fail:
        puts("-1");
    end:;
    }
    return 0;
}