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
const int maxn = 1e5 + 100;
int T, n, a[maxn], m, L[maxn], R[maxn];
inline void opt(int l, int r)
{
    L[++m] = l, R[m] = r;
    if ((a[l] + a[r]) & 1)
        a[r] = a[l];
    else
        a[l] = a[r];
}
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        m = 0;
        for (int i = 1; i <= n; ++i) read(a[i]);
        if(n == 1)
        {
            puts("0");
            continue;
        }
        opt(1, n);
        for(int i = 2;i<n;++i)
        {
            if ((a[i] + a[1]) & 1)
                opt(1, i);
            else
                opt(i, n);
        }
        printf("%d\n", m);
        for (int i = 1; i <= m; ++i) printf("%d %d\n", L[i], R[i]);
//        for (int i = 1; i <= n; ++i) printf("%d ",a[i]);
//        puts("");
    }
    return 0;
}