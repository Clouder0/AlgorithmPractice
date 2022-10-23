#include <cstdio>
#include <algorithm>
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
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e6 + 100;
int n, to[maxn], w[maxn], in[maxn], q[maxn], qh = 1, qt;
long long maxx[maxn], diameter[maxn], ans;
long long solve(int u)
{
    int start = u;
    long long res1 = diameter[u], res2 = -(1ll << 60), addmax = maxx[u], minusmax = maxx[u];
    long long presum = w[u];
    in[u] = 0, u = to[u];
    while (u != start)
    {
        in[u] = 0;
        res1 = max(res1, diameter[u]);
        res1 = max(res1, maxx[u] + presum + minusmax);
        res2 = max(res2, maxx[u] - presum + addmax);
        minusmax = max(minusmax, maxx[u] - presum);
        addmax = max(addmax, maxx[u] + presum);
        presum += w[u], u = to[u];
    }
    return max(res1, res2 + presum);
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(to[i]), read(w[i]), in[to[i]]++;
    for (int i = 1; i <= n; ++i) if (!in[i]) q[++qt] = i;
    while (qt >= qh)
    {
        int u = q[qh++], v = to[u];
        long long t = maxx[u] + w[u];
        diameter[v] = max(diameter[v], t + maxx[v]);
        diameter[v] = max(diameter[v], diameter[u]);
        maxx[v] = max(maxx[v], t);
        if (--in[v] == 0) q[++qt] = v;
    }
    for (int i = 1; i <= n; ++i) if (in[i]) ans += solve(i);
    printf("%lld\n", ans);
    return 0;
}