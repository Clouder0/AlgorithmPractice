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
const int maxn = 3e5 + 100;
int T, n, a[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i) read(a[i]);
        int flag = 1;
        for (int i = 1; i < n; ++i) flag &= (a[i] == a[i + 1]);
        if(flag){puts("-1");continue;}
        int maxx = 0;
        for (int i = 1; i <= n; ++i) maxx = std::max(maxx, a[i]);
        int pos = 0;
        for (int i = 1; !pos && i <= n; ++i)
            if (a[i] == maxx && ((i < n && a[i] > a[i + 1]) || (i > 1 && a[i] > a[i - 1]))) pos = i;
        printf("%d\n", pos);
    }
    return 0;
}