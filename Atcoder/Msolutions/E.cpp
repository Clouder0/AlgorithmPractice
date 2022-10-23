#include <cstdio>
#include <bitset>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
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
const int maxn = 19;
int n;
int X[maxn],Y[maxn],P[maxn];
long long xdis[maxn][maxn],ydis[maxn][maxn];
long long xval[maxn][1<<maxn],yval[maxn][1<<maxn];
long long ans[maxn];
int id[maxn];
template<typename T>
inline T abs(const T &x) {return x > 0 ? x : -x;}
int main()
{
    read(n);
    for (int i = 0; i < n; ++i) read(X[i]), read(Y[i]), read(P[i]);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) xdis[i][j] = abs(X[i] - X[j]), ydis[i][j] = abs(Y[i] - Y[j]);
    for (int i = 0; i <= n; ++i) ans[i] = 1ll << 62;
    int maxx = (1 << n) - 1;
    for (int i = 0; i <= maxx; ++i)
        for (int j = 0; j < n; ++j)
        {
            xval[j][i] = abs(X[j]), yval[j][i] = abs(Y[j]);
            for (int k = 0; k < n; ++k) if (i & (1 << k))  xval[j][i] = std::min(xval[j][i], xdis[k][j]), yval[j][i] = std::min(yval[j][i], ydis[k][j]);
            xval[j][i] *= P[j],yval[j][i] *= P[j];
        }
    for (int i = 0; i <= maxx; ++i)
    {
        int num = 0;
        for (int j = i; j > 0; j >>= 1) num += j & 1;
        for (int j = i; j >= 0; --j)
        {
            j &= i;
            long long tans = 0;
            for (int k = 0; k < n; ++k) if (!((1 << k) & i)) tans += std::min(xval[k][j],yval[k][(~j) & i]);
            ans[num] = std::min(ans[num], tans);
        }
    }
    for (int i = 0; i <= n; ++i) printf("%lld\n", ans[i]);
    return 0;
}