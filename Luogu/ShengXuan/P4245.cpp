#include <cstdio>
#include <algorithm>
#include <cmath>
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
const int O = 1 << 15;
const long double PI = 3.141592653589793238462643383279502114197169;
int n, m, P, R[maxn], A[maxn], B[maxn];
struct comp
{
    long double x, y;
    comp(long double nx = 0, long double ny = 0) { x = nx, y = ny; }
} A0[maxn], B0[maxn], A1[maxn], B1[maxn], step[maxn], T[maxn], T2[maxn];
comp operator+(const comp& a, const comp& b) { return comp(a.x + b.x, a.y + b.y); }
comp operator-(const comp& a, const comp& b) { return comp(a.x - b.x, a.y - b.y); }
comp operator*(const comp& a, const comp& b) { return comp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
comp operator*(const comp& a, const long double& b) { return comp(a.x * b, a.y * b); }
void DFT(comp* f, int n, int rev)
{
    for (int i = 1; i < n; ++i) if (i < R[i]) std::swap(f[i], f[R[i]]);
    for (int h = 2; h <= n; h <<= 1)
    {
        comp w(std::cos(2 * PI / h), rev * std::sin(2 * PI / h));
        step[0] = comp(1, 0);
        for (int i = 1; i < (h >> 1); ++i) step[i] = step[i - 1] * w;
        for (int i = 0; i < n; i += h)
            for (int j = i; j < i + (h >> 1); ++j)
            {
                comp t1 = f[j], t2 = step[j - i] * f[j + (h >> 1)];
                f[j] = t1 + t2, f[j + (h >> 1)] = t1 - t2;
            }
    }
    if(rev == -1) for (int i = 0; i < n; ++i) f[i].x /= n, f[i].y /= n;
}
long long C0[maxn], C1[maxn], C2[maxn];
const comp I = comp(0, 1);
void FDFT(comp *A,comp *B,int limit)
{
    for (int i = 0; i < limit; ++i) T[i].x = A[i].x, T[i].y = B[i].x;
    DFT(T, limit, 1);
    T2[0].x = T[0].x, T2[0].y = -T[0].y;
    for (int i = 1; i < limit; ++i) T2[i].x = T[limit - i].x, T2[i].y = -T[limit - i].y;
    for (int i = 0; i <= limit; ++i)
    {
        A[i] = T[i] + T2[i], A[i] = A[i] * 0.5;
        B[i] = T2[i] - T[i], B[i] = B[i] * I * 0.5;
    }
}
int main()
{
    read(n), read(m), read(P);
    for (int i = 0; i <= n; ++i) read(A[i]);
    for (int i = 0; i <= m; ++i) read(B[i]);
    int limit = 1;
    while(limit <= n + m) limit <<= 1;
    for (int i = 1; i <= limit; ++i) R[i] = (R[i >> 1] >> 1) | ((i & 1) * (limit >> 1));
    for (int i = 0; i <= n; ++i) A0[i].x = A[i] & (O - 1), A1[i].x = A[i] >> 15;
    for (int i = 0; i <= m; ++i) B0[i].x = B[i] & (O - 1), B1[i].x = B[i] >> 15;
    FDFT(A0, A1, limit), FDFT(B0, B1, limit);

    for (int i = 0; i <= limit; ++i) T[i] = (A0[i] * B0[i]) + I * (A0[i] * B1[i]);
    DFT(T, limit, -1);
    for (int i = 0; i <= n + m; ++i) C0[i] = (long long)(T[i].x + 0.5);
    for (int i = 0; i <= n + m; ++i) C1[i] += (long long)(T[i].y + 0.5);

    for (int i = 0; i <= limit; ++i) T[i] = (A1[i] * B0[i]) + I * (A1[i] * B1[i]);
    DFT(T, limit, -1);
    for (int i = 0; i <= n + m; ++i) C1[i] += (long long)(T[i].x + 0.5);
    for (int i = 0; i <= n + m; ++i) C2[i] = (long long)(T[i].y + 0.5);

    long long M1 = O % P, M2 = M1 * M1 % P;
    for (int i = 0; i <= n + m; ++i)
    {
        long long res = C0[i] % P;
        res = (res + C1[i] % P * M1 % P) % P;
        res = (res + C2[i] % P * M2 % P) % P;
        printf("%lld ",res);
    }
    return 0;
}