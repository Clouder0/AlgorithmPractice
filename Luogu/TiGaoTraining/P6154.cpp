#include <cstdio>
#include <vector>
#include <algorithm>
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
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
#define int long long
const int mod = 998244353;
const int maxn = 1e5 + 100;
vector<int> E[maxn];
int n, m;
int f[maxn], g[maxn], in[maxn];
int q[maxn], qh, qt;
int fastpow(int x,int k)
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = (1ll * res * x) % mod;
        x = (1ll * x * x) % mod;
        k >>= 1;
    }
    return res;
}
int inv(int x) { return fastpow(x, mod - 2); }
signed main()
{
    read(n), read(m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x), read(y), E[x].push_back(y), in[y]++;
    }
    qh = 1, qt = 0;
    for (int i = 1; i <= n; f[i] = 1, ++i) if (in[i] == 0) q[++qt] = i;
    while(qt >= qh)
    {
        int u = q[qh++];
        for (vector<int>::iterator it = E[u].begin(); it != E[u].end(); ++it)
        {
            int v = *it;
            (f[v] += f[u]) %= mod;
            (g[v] += g[u] + f[u]) %= mod;
            if (--in[v] == 0) q[++qt] = v;
        }
    }
    int sf = 0,sg = 0;
    for (int i = 1; i <= n; ++i) sf = (sf + f[i]) % mod, sg = (sg + g[i]) % mod;
    printf("%lld\n", (1ll * sg * inv(sf)) % mod);
    return 0;
}