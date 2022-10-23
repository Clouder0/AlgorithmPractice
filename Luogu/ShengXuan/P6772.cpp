#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
inline char nc()
{
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 260;
const long long INF = 1ll << 61;
int n, m, T, K;
int w[maxn], num[maxn][6], cnt;
struct Matrix
{
    int n, m;
    long long a[maxn][maxn];
    Matrix() {}
    Matrix(int n, int m, long long val)
    {
        this->n = n, this->m = m;
        for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) a[i][j] = val;
    }
    Matrix operator*(const Matrix b)
    {
        Matrix c(n, m, -INF);
        for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) for (int k = 1; k <= b.m; ++k)
            c.a[i][k] = max(c.a[i][k], a[i][j] + b.a[j][k]);
        return c;
    }
    void clear() { memset(a, ~0x3f, sizeof(a)); }

} G[40];
struct fes
{
    int x, y;
    long long t;
} F[maxn];
bool cmp(const fes a, const fes b) { return a.t < b.t; }
int main()
{
//    freopen("delicacy.in", "r", stdin);
//    freopen("delicacy.out", "w", stdout);
    read(n), read(m), read(T), read(K);
    for (int i = 1; i <= n; ++i) read(w[i]);
    G[0].clear();
    for (int i = 1; i <= n; ++i) num[i][1] = ++cnt;
    for (int i = 1; i <= m; ++i)
    {
        int u, v, t;
        read(u), read(v), read(t);
        if (!num[u][t])
        {
            for (int j = 2; j <= 5; ++j) num[u][j] = ++cnt;
            for (int j = 2; j <= 5; ++j) G[0].a[num[u][j - 1]][num[u][j]] = 0;
        }
        G[0].a[num[u][t]][v] = w[v];
    }
    G[0].n = G[0].m = cnt;
    for (int i = 1; i <= K; ++i) read(F[i].t), read(F[i].x), read(F[i].y);
    sort(F + 1, F + 1 + K, cmp);
    F[++K].t = T, F[K].x = 1, F[K].y = 0;
    long long maxt = 0;
    int maxx = 0;
    for (int i = 1; i <= K; ++i) maxt = max(maxt, F[i].t - F[i - 1].t);
    while ((1ll << maxx) < maxt) ++maxx;
    for (int i = 1; i <= maxx; ++i) G[i] = G[i - 1] * G[i - 1];
    Matrix now(1, cnt, -INF);
    now.a[1][1] = w[1];
    for (int i = 1; i <= K; ++i)
    {
        int dt = F[i].t - F[i - 1].t;
        for (int j = maxx; j >= 0; --j) if (dt & (1ll << j)) now = now * G[j];
        now.a[1][F[i].x] += F[i].y;
    }
    if (now.a[1][1] < 0) puts("-1");
    else printf("%lld\n", now.a[1][1]);
    return 0;
}