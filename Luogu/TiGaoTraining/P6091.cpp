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
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e6 + 100;
int T, n, d;
bool hasrt[maxn], notprime[maxn];
int primes[maxn], primecnt;
void init()
{
    const int top = 1e6;
    for (int i = 2; i <= top; ++i)
    {
        if (!notprime[i]) primes[++primecnt] = i;
        for (int j = 1; j <= primecnt && 1ll * primes[j] * i <= top; ++j)
        {
            notprime[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
    hasrt[2] = hasrt[4] = 1;
    for (int i = 2; i <= primecnt; ++i)
    {
        for (long long j = primes[i]; j <= top; j *= primes[i]) hasrt[j] = 1;
        for (long long j = 2 * primes[i]; j <= top; j *= primes[i]) hasrt[j] = 1;
    }
}
int getvalphi(int x)
{
    long long res = x;
    for (int i = 2; 1ll * i * i <= x; ++i)
    {
        if (x % i != 0) continue;
        while (x % i == 0) x /= i;
        res = res / i * (i - 1);
    }
    if (x > 1) res = res / x * (x - 1);
    return res;
}
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int fastpow(int x, int k, int mod)
{
    int res = 1;
    for (; k; k >>= 1)
    {
        if (k & 1) res = 1ll * res * x % mod;
        x = 1ll * x * x % mod;
    }
    return res;
}
int P[maxn], pcnt, G[maxn], gcnt;
int main()
{
    init();
    read(T);
    while (T--)
    {
        gcnt = pcnt = 0;
        read(n), read(d);
        if (!hasrt[n])
        {
            puts("0"), puts("");
            continue;
        }
        int phin = getvalphi(n), x = phin;
        for (int i = 2; 1ll * i * i <= x; ++i)
            if (x % i == 0)
            {
                P[++pcnt] = i;
                while (x % i == 0) x /= i;
            }
        if (x != 1) P[++pcnt] = x;
        int ming = 0;
        for (int i = 1; i < n; ++i)
        {
            if (gcd(i, n) != 1) continue;
            for (int j = 1; j <= pcnt; ++j) if (fastpow(i, phin / P[j], n) == 1) goto end;
            ming = i;
            break;
        end:;
        }
        G[++gcnt] = ming;
        for (int i = 2; i <= phin; ++i)
        {
            if (gcd(i, phin) != 1) continue;
            G[++gcnt] = fastpow(ming, i, n);
        }
        printf("%d\n", gcnt);
        std::sort(G + 1, G + 1 + gcnt);
        for (int i = d; i <= gcnt; i += d) printf("%d ", G[i]);
        puts("");
    }
    return 0;
}