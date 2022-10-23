#include <cstdio>
#include <algorithm>
#include <ctype.h>
#include <cmath>
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
const int maxn = 1e5 + 100;
const long double eps = 1e-7;
int n, m, k, a[maxn], is[maxn];
long double f[maxn], x[maxn], sum[maxn], sumx[maxn];
int main()
{
    read(n), read(m), read(k);
    for (int i = 1; i <= k; ++i) read(a[i]), is[a[i]] = 1;
    //for (int i = n + m + 10; i >= n; --i) f[i] = 1.0, sum[i] = sum[i + 1] + f[i];
    for (int i = n - 1; i >= 0; --i)
    {
        if (is[i]) f[i] = 0, x[i] = 1;
        else f[i] = (sum[i + 1] - sum[i + 1 + m]) / m + 1.0, x[i] = (sumx[i + 1] - sumx[i + 1 + m]) / m;
        sum[i] = sum[i + 1] + f[i];
        sumx[i] = sumx[i + 1] + x[i];
    }
    //for(int i = 0;i<=n + 1;++i) printf("%d %.2f %.2f\n",i,f[i],x[i]);
    if(fabs(x[0] - 1.0) <= eps) return puts("-1"),0;
    long double xx = (f[0]) / (1.0 - x[0]);
    printf("%.4f", (double)(f[0] + x[0] * xx));
    return 0;
}