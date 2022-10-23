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
const int maxn = 1100;
int T, n;
int notprime[maxn], primes[maxn], cnt;
int a[maxn][maxn];
int main()
{
    for (int i = 2; i <= 1000; ++i)
    {
        if (!notprime[i]) primes[++cnt] = i;
        for (int j = 1; j <= cnt && primes[j] * i <= 1000; ++j)
        {
            notprime[i * primes[j]] = 1;
            if ((i % primes[j]) == 0) break;
        }
    }
    read(T);
    while(T--)
    {
        read(n);
        if(n == 1) { puts("1"); continue; }
        int p = 5;
        while(primes[p] - (n - 1) <= 2) ++p;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) a[i][j] = 1;
        for (int i = 1; i <= n; ++i) a[i][i] = primes[p] - (n - 1);
        if (((primes[p] - (n - 1)) & 1))
        {
            for (int i = 1; i <= n; ++i) a[i][i]++;
            for (int i = 2; i <= n; ++ i) a[i - 1][i]--;
            a[n][1]--;
        }
        for (int i = 1; i <= n; puts(""), ++i)
            for (int j = 1; j <= n; ++j) printf("%d ", a[i][j]);
    }
    return 0;
}