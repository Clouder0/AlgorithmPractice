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
const int maxn = 1e6 + 100;
int n;
double p[maxn], rp[maxn];
int main()
{
    read(n);
    for (int i = 1, x; i <= n; ++i) read(x), p[i] = x / 1000000.0, rp[i] = 1.0 - p[i];
    double res = 0.0,ans = p[1],prod = rp[1];
    for (int l = 1, r = 1; l <= n; ++l)
    {
        if (l > r) l = r, ans = p[l], prod = rp[l];
        while (r < n && ans <= prod) ans = ans * rp[r + 1] + p[r + 1] * prod, prod = prod * rp[r + 1], ++r;
        res = std::max(res, ans);
        prod /= (1.0 - p[l]), ans = (ans - p[l] * prod) / (1.0 - p[l]);
    }
    printf("%d",(int)(res * 1000000.0));
    return 0;
}