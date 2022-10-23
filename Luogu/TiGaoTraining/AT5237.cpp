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
const int maxn = 1e5 + 100;
int n, m;
int main()
{
    read(n), read(m);
    if(n & 1) for (int i = 1; i <= m; ++i) printf("%d %d\n", i, n - i + 1);
    else
    {
        int mid = n / 2 - 1;
        int l = 1;
        while (m && l < mid) printf("%d %d\n", l++, mid--), --m;
        mid = n / 2;
        int r = n - 1;
        while (m && mid < r) printf("%d %d\n", mid++, r--), --m;
    }
    return 0;
}