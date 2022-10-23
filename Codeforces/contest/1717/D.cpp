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
const int mod = 1e9 + 7;
int n, k;
int fastpow(int a,int b)
{
    int res = 1;
    int base = a;
    while(b)
    {
        if(b & 1) res = (1ll * res * base) % mod;
        b >>= 1;
        base = 1ll * base * base % mod;
    }
    return res;
}
int main()
{
    read(n), read(k);
//    printf("%d\n",fastpow(2,3));
    if(k == 0) puts("1");
    else if (k >= n) printf("%d\n", fastpow(2, n));
    else printf("%d\n", (fastpow(2,n) + mod - fastpow(2,n-k) + 1) % mod);
    return 0;
}