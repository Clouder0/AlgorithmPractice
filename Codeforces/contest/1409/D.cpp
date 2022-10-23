#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
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
long long T,n,s;
int a[100],cnt;
long long ten[100];
int main()
{
    read(T);
    ten[1] = 1;
    for (int i = 2; i <= 18; ++i)  ten[i] = ten[i-1] * 10;
    while(T--)
    {
        read(n), read(s);
        cnt = 0;
        while (n) a[++cnt] = n % 10, n /= 10;
        int sum = 0;
        for (int i = 1; i <= cnt; ++i) sum += a[i];
        long long res = 0;
        while(sum > s)
        {
            int maxx = cnt;
            for (int i = cnt; i; --i) if(a[i]) maxx = i;
            res += ten[maxx] * (10 - a[maxx]);
            sum -= a[maxx] - 1;
            a[maxx] = 0, a[maxx + 1]++;
            if (a[cnt + 1]) ++cnt;
        }
        printf("%lld\n",res);
    }
    return 0;
}