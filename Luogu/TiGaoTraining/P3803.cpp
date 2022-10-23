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
const int maxn = 3e6 + 100;
const int mod = 998244353;
int step[maxn], R[maxn], F[maxn], G[maxn], n, m;
inline int add(int x, int y) { int t = x + y; return t >= mod ? t - mod : t; }
inline int add(int x, int y,int mod) { int t = x + y; return t >= mod ? t - mod : t; }
inline int mul(int x, int y) { long long res = 1ll * x * y; return res >= mod ? res % mod : res; }
inline int mul(int x, int y,int mod) { long long res = 1ll * x * y; return res >= mod ? res % mod : res; }
int fastpow(int x, int k)
{
    int res = 1;
    for (; k; x = mul(x, x), k >>= 1)
        if (k & 1) res = mul(res, x);
    return res;
}
int fastpow(int x, int k,int mod)
{
    int res = 1;
    for (; k; x = mul(x, x), k >>= 1)
        if (k & 1) res = mul(res, x);
    return res;
}
void NTT(int* f, int n, int rev)
{
    for (int i = 1; i < n; ++i) if (R[i] < i) std::swap(f[i], f[R[i]]);
    for (int h = 2; h <= n; h <<= 1)
    {
        int w = fastpow(3, (mod - 1) / h);
        if (rev == -1) w = fastpow(w, mod - 2);
        step[0] = 1;
        for (int i = 1; i < (h >> 1); ++i) step[i] = mul(step[i - 1], w);
        for (int i = 0; i < n; i += h)
            for (int j = i; j < i + (h >> 1); ++j)
            {
                int A = f[j], B = mul(f[j + (h >> 1)], step[j - i]);
                f[j] = add(A, B), f[j + (h >> 1)] = add(A, mod - B);
            }
    }
}
void DFT(int* f, int n, int rev, int mod)
{
    for (int i = 1; i < n; ++i) if (R[i] < i) std::swap(f[i], f[R[i]]);
    for (int h = 2; h <= n; h <<= 1)
    {
        int w = fastpow(3, (mod - 1) / h, mod);
        if (rev == -1) w = fastpow(w, mod - 2, mod);
        step[0] = 1;
        for (int i = 1; i < (h >> 1); ++i) step[i] = mul(step[i - 1], w, mod);
        for (int i = 0; i < n; i += h)
            for (int j = i; j < i + (h >> 1); ++j)
            {
                int t1 = f[j], t2 = mul(step[j - i], f[j + (h >> 1)], mod);
                f[j] = add(t1, t2, mod), f[j + (h >> 1)] = add(t1, mod - t2, mod);
            }
    }
    if(rev == -1) 
    {
        int inv = fastpow(n, mod - 2, mod);
        //for (int i = 0; i < n; ++i) f[i] = mul(f[i], inv, mod);
    }
}
int main()
{
    read(n), read(m);
    for (int i = 0; i <= n; ++i) read(F[i]);
    for (int i = 0; i <= m; ++i) read(G[i]);
    int limit = 1;
    while (limit <= n + m) limit <<= 1;
    for (int i = 1; i <= limit; ++i) R[i] = (R[i >> 1] >> 1) | ((i & 1) * (limit >> 1));
    //NTT(F, limit, 1), NTT(G, limit, 1);
    DFT(F,limit,1,mod),DFT(G,limit,1,mod);
    for (int i = 0; i <= limit; ++i) F[i] = mul(F[i], G[i]);
//    NTT(F, limit, -1);
	DFT(F,limit,-1,mod);
    int inv = fastpow(limit, mod - 2);
    for (int i = 0; i <= n + m; ++i) printf("%d ", mul(F[i], inv));
    return 0;
}