#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c);) c = nc();
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 1e5 + 100;
int n, m, a[maxn];
namespace ST
{
int f[maxn][20];
int lg[maxn];
void init()
{
    for (int i = 1; i <= n; ++i) f[i][0] = a[i];

    lg[2] = 1;
    for (int i = 3; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
    for (int j = 1; j <= lg[n]; ++j)
        for (int i = 1, len = (1 << (j - 1)); i + len <= n; ++i)
            f[i][j] = std::max(f[i][j - 1], f[i + len][j - 1]);
}
inline int ask(int l, int r)
{
    int k = lg[r - l + 1];
    return std::max(f[l][k], f[r - (1 << k) + 1][k]);
}
}  // namespace ST
int main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    ST::init();
    while(m--)
    {
        int l, r;
        read(l), read(r), printf("%d\n", ST::ask(l, r));
    }
    return 0;
}