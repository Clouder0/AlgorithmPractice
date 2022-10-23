#include <cstdio>
#include <algorithm>
#include <cstring>
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
inline void read(char *s)
{
    static char c;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) *s++ = c;
    *s = '\0';
}
const int maxn = 3e6 + 100;
struct comp
{
    double x, y;
    comp(const double nx = 0, const double ny = 0) { x = nx, y = ny; }
} f[maxn], tmp[maxn];
comp operator+(const comp& a, const comp& b) { return comp(a.x + b.x, a.y + b.y); }
comp operator-(const comp& a, const comp& b) { return comp(a.x - b.x, a.y - b.y); }
comp operator*(const comp& a, const comp& b) { return comp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
int R[maxn];
const double PI = 3.141592653589793238462;
void change(comp* f, int n)
{
    static int R[maxn], top = 1;
    if (top < n - 1)
    {
    	for (int i = top; i < n; ++i) R[i] = (R[i >> 1] >> 1) | ((i & 1) * (n >> 1));
        top = n - 1;
    }
    for (int i = 0; i < n; ++i) if (i < R[i]) std::swap(f[i], f[R[i]]);
}
void DFT(comp* f, int n, int rev)
{
    change(f, n);
    for (int h = 2; h <= n; h <<= 1)
    {
        comp w = comp(cos(2.0 * PI / h), rev * sin(2.0 * PI / h));
        tmp[0] = comp(1, 0);
        for (int i = 1; i < (h >> 1); ++i) tmp[i] = tmp[i - 1] * w;
        for (int i = 0; i < n; i += h)
            for (int j = i; j < i + (h >> 1); ++j)
            {
                comp F = f[j], G = tmp[j - i] * f[j + (h >> 1)];
                f[j] = F + G, f[j + (h >> 1)] = F - G;
            }
    }
}
int n, m;
char A[maxn], B[maxn];
int C[maxn];
int main()
{
    read(A), read(B), n = strlen(A), m = strlen(B);
    for (int i = 0; i < n; ++i) f[i].x = A[n - i - 1] - '0';
    for (int i = 0; i < m; ++i) f[i].y = B[m - i - 1] - '0';
    int limit = 1;
    while (limit < n + m - 1) limit <<= 1;
    DFT(f, limit, 1);
    for (int i = 0; i <= limit; ++i) f[i] = f[i] * f[i];
    DFT(f, limit, -1);
    for (int i = 0; i <= limit; ++i) C[i] = (int)(f[i].y / 2 / limit + 0.5);
    for(int i = 0; i <= limit; ++i) if (C[i] > 9) C[i + 1] += C[i] / 10, C[i] %= 10; 
    while (C[limit] > 9) C[limit + 1] += C[limit] / 10, C[limit] %= 10, ++limit;
    while(limit > 0 && C[limit] == 0) --limit;
    for (int i = limit; i >= 0; --i) putchar(C[i] + '0');
    return 0;
}