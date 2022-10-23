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
const int maxn = 1e3 + 100;
int T,n,a[maxn],b[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        int zero = 0,one = 0;
        for (int i = 1; i <= n; ++i) read(a[i]), zero += a[i] ^ 1, one += a[i];
        if(zero >= n / 2)
        {
            printf("%d\n",zero);
            for (int i = 1; i <= zero; ++i) printf("0 ");
            puts("");
        }
        else
        {
            if(one & 1) one--;
            printf("%d\n",one);
            for (int i = 1; i <= one; ++i) printf("1 ");
            puts("");
        }
    }
    return 0;
}