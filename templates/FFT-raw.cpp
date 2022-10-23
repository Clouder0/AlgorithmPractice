#include <cstdio>
#include <algorithm>
#include <cmath>
#include <ctype.h>
const int bufSize = 1e6;
//#define DEBUG
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
const int maxn = 4e6 + 100;
const double PI = 3.1415926535897932384626433832;
struct comp
{
    double x, y;
    comp(double nx = 0, double ny = 0) { x = nx, y = ny; }
} f[maxn], g[maxn], tmp[maxn];
comp operator+( comp a,  comp b) { return comp(a.x + b.x, a.y + b.y); }
comp operator-( comp a,  comp b) { return comp(a.x - b.x, a.y - b.y); }
comp operator*( comp a,  comp b) { return comp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
void DFT(comp* f, int n, int rev = 1)
{
    if (n == 1) return;
    for (int i = 0; i < n; ++i) tmp[i] = f[i];
    for (int i = 0; i < n; i += 2) f[i >> 1] = tmp[i];               //0,2,4,8,...,n - 2 left
    for (int i = 1; i < n; i += 2) f[(n >> 1) + (i >> 1)] = tmp[i];  //1,3,5,...,n - 1 right
    comp* F = f, *G = f + (n >> 1);
    DFT(F, n >> 1, rev), DFT(G, n >> 1, rev);
    comp now = comp(1, 0), w = comp(cos(2.0 * PI / n), rev * sin(2.0 * PI / n));
    for (int i = 0; i < (n >> 1); ++i)
    {
        tmp[i] = F[i] + now * G[i];
        tmp[i + (n >> 1)] = F[i] - now * G[i];
        now = now * w;
    }
    for (int i = 0; i < n; ++i) f[i] = tmp[i];
}
int n, m;
int main()
{
    read(n), read(m);
    for (int i = 0; i <= n; ++i) read(f[i].x);
    for (int i = 0; i <= m; ++i) read(g[i].x);
    int limit = 1;
    while (limit <= n + m) limit <<= 1;
    DFT(f, limit, 1), DFT(g, limit, 1);
    for (int i = 0; i <= limit; ++i) f[i] = f[i] * g[i];
    DFT(f, limit, -1);
    for (int i = 0; i <= n + m; ++i) printf("%d ", (int)(f[i].x / limit + 0.5));
    return 0;
}