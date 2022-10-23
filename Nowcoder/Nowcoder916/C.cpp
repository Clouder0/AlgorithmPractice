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
int T;
long long n, k, a, b;
int main()
{
    read(T);
    while (T--)
    {
        read(n), read(k), read(a), read(b);
        if(a > b) std::swap(a,b);
        long long al = a - k, ar = a + k, bl = b - k, br = b + k;
        if(a == b) goto YES;
        if(a <= k + 1 && a + k >= n) goto NO;
//        if (ar < b) goto YES;
        // if(al <= 1 && ar >= n) goto NO;
        if(bl > 1) goto YES;
        if(br < n) goto YES;
        goto NO;
    YES:
        puts("YES");
        continue;
    NO:
        puts("NO");
        continue;
    }
    return 0;
}