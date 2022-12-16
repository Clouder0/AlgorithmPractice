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
int T,n,a[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i) read(a[i]);
        int sum = 0;
        if(a[1] == 0)
        {
            puts("Bob");
            goto end;
        }
        for (int i = 2; i <= n; ++i)
            if (a[i] == 0)
            {
                puts("Alice");
                goto end;
            }
        for (int i = 1; i <= n; ++i) sum ^= (a[i] & 1);
        if (sum)
            puts("Alice");
        else
            puts("Bob");
        end:;
    }
    return 0;
}