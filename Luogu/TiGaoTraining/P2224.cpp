#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
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
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 6e3 + 100;
int n, t1[maxn], t2[maxn], t3[maxn], sum[maxn];
int f[2][5 * maxn];
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(t1[i]), read(t2[i]), read(t3[i]), sum[i] = sum[i - 1] + max(t1[i], t3[i]);
    int now = 0, last = 1;
    memset(f, 0x3f, sizeof(f));
    f[last][0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= sum[i]; ++j)
        {
            f[now][j] = 1 << 30;
            if (t2[i]) f[now][j] = f[last][j] + t2[i];
            if (t1[i] && j >= t1[i]) f[now][j] = min(f[now][j], f[last][j - t1[i]]);
            if (t3[i] && j >= t3[i]) f[now][j] = min(f[now][j], f[last][j - t3[i]] + t3[i]);
        }
        now ^= 1, last ^= 1;
    }
    int ans = 1 << 30;
    for (int i = 1; i <= sum[n]; ++i) ans = min(ans, max(f[last][i], i));
    printf("%d\n", ans);
    return 0;
}