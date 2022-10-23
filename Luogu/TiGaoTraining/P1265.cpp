#include <cstdio>
#include <cmath>
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
const int maxn = 5100;
int n, X[maxn], Y[maxn];
double calc(int a, int b) { return sqrt(1.0 * (X[a] - X[b]) * (X[a] - X[b]) + 1.0 * (Y[a] - Y[b]) * (Y[a] - Y[b])); }
double dis[maxn];
bool vis[maxn];
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(X[i]), read(Y[i]);
    for (int i = 2; i <= n; ++i) dis[i] = 1e18;
    double ans = 0;
    dis[0] = 1e17;
    for (int k = 1; k <= n; ++k)
    {
        int u = 0;
        for (int i = 1; i <= n; ++i) if (!vis[i] && dis[i] < dis[u]) u = i;
        if(!u) break;
        vis[u] = 1, ans += dis[u];
        for (int i = 1; i <= n; ++i) if (!vis[i] && dis[i] > calc(i, u)) dis[i] = calc(i, u);
    }
    printf("%.2f",ans);
    return 0;
}