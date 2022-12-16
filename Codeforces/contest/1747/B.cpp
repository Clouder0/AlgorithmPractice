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
int T,n;
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        if(n == 1)
        {
            puts("1");
            puts("1 2");
            continue;
        }
        printf("%d\n", (n + 1) >> 1);
        for (int i = 1; 2 * i <= n + 1; ++i)
            printf("%d %d\n", 3 * (i-1) + 1, 3 * (n - i + 1));
    }
    return 0;
}