#include <cstdio>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    r = 0;
    for(c = nc();!isdigit(c);c = nc());
    for(;isdigit(c);c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 1e6 + 100;
int n, h[maxn], m, k;
int f[maxn],q[maxn],qt,qh; 
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(h[i]);
    read(m);
    while(m--)
    {
        read(k);
        f[1] = 0;
        for (int i = 2; i <= n; ++i) f[i] = 1 << 30;
        qt = qh = 1, q[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            while (qt >= qh && q[qh] < i - k) ++qh;
            f[i] = f[q[qh]] + (h[i] >= h[q[qh]]);
            while (qt >= qh && (f[q[qt]] > f[i] || (f[q[qt]] == f[i] && h[q[qt]] <= h[i]))) --qt;
            q[++qt] = i;
        }
        printf("%d\n",f[n]);
    }
    return 0;
}