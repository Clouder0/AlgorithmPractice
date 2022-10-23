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
const int maxn = 2e5 + 100;
int T, n, a[maxn], to[maxn], b[maxn], cnt;
int main()
{
    read(T);
    while(T--)
    {
        cnt = 0;
        read(n);
        for (int i = 1; i <= n; ++i) read(a[i]), to[i] = 0;
        for (int l = 2; l <= n; ++l)
        {
            int r = l;
            while (r < n && a[r + 1] > a[r]) ++r;
            for (int i = l; i <= r; ++i) to[i] = r;
            b[++cnt] = r - l + 1;
            l = r;
        }
        int sonnum = 1, l = 1, r = 1, dep = 0;
        while (1)
        {
            int newnum = 0;
            for (int i = l; i <= r; ++i) newnum += b[i];
            sonnum = newnum, l = r + 1, r = l + sonnum - 1;
            if (l > n) break;
            ++dep;
        }
        printf("%d\n", dep);
    }
    return 0;
}