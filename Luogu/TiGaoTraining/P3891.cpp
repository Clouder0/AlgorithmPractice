#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctype.h>
using namespace std;
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
const int maxn = 110,maxm = 1100;
int n,m,t;
int a[maxn],b[maxn];
int f[maxm],g[maxm][maxm];
int main()
{
    read(n),read(m),read(t);
    if (m >= t) { puts("0"); return 0; }
    for (int i = 1; i <= n; ++i) read(a[i]), read(b[i]);
    for (int i = 1; i <= n; ++i) for (int j = a[i]; j <= t; ++j) f[j] = max(f[j], f[j - a[i]] + b[i]);
    memset(g, -1, sizeof(g));
    g[0][m] = 0;
    for (int i = 0; i <= t; ++i)
    {
        if (g[i][t] != -1) { printf("%d\n", i); return 0; }
        //time
        for (int j = 0; j <= t; ++j)
        {
            //now have
            if(g[i][j] == -1) continue;
            for (int k = 0; k <= j; ++k)
            {
                if (f[k] == -1) continue;
                int nx = j - k + f[k] + g[i][j];
                if (nx >= t) { printf("%d\n", i + 1); return 0; }
                g[i + 1][nx] = max(g[i + 1][nx], g[i][j] + f[k]);
            }
        }
    }
    return 0;
}