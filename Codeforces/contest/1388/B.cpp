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
int f[5] = {0,0,2,4,8};
const int maxn = 2e5 + 100;
int T,n;
int a[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        int x = n,cnt = 0;
        while(x > 0)
        {
            x -= 4,a[++cnt] = 8;
        }
        while(cnt < n) a[++cnt] = 9;
        for(int i = n;i;--i) printf("%d",a[i]);
        putchar('\n');
    }
    return 0;
}