#include <cstdio>
#include <cstring>
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T>
void read(T &r)
{
    static char c; r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 51;
const int maxx = 1 << 7;
int n, m;
int a[maxn][maxn];
int f[2][maxx][maxx];
int g[2][maxx][maxx];
int csa[maxn][maxx];
inline int calc(int x, int status)
{
    if (csa[x][status]) return csa[x][status];
    int res = 0;
    for (int i = 0; i < m; ++i) if (status & (1 << i)) res += a[x][i + 1];
    return csa[x][status] = res;
}
int nsa[maxx];
inline int getnum(int status)
{
    if (nsa[status]) return nsa[status];
    for (int i = 0; i < m; ++i) if (status & (1 << i)) ++nsa[status];
    return nsa[status];
}
int maxs;
inline bool check(int a, int b, int c){return ((a | (a << 1) | (a >> 1) | b | c) & (maxs - 1)) == (maxs - 1);}
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) read(a[i][j]);
    memset(f, 0x3f, sizeof(f));
    maxs = 1 << m;
    int now = 1, last = 0;
    for (int i = 0; i < maxs; ++i) f[now][i][0] = calc(1, i), g[now][i][0] = getnum(i);
    now ^= 1, last ^= 1;
    for (int i = 2; i < n; ++i)
    {
        memset(f[now], 0x3f, sizeof(f[now]));
        for (int j = 0; j < maxs; ++j) for (int k = 0; k < maxs; ++k) for (int p = 0; p < maxs; ++p)
            if (check(k, j, p))
            {
                int x = f[last][k][p] + calc(i, j), y = g[last][k][p] + getnum(j);
                if (f[now][j][k] > x) f[now][j][k] = x, g[now][j][k] = y;
                else if (f[now][j][k] == x && g[now][j][k] > y) g[now][j][k] = y;
            }
        now ^= 1, last ^= 1;
    }
    int ans = 1 << 30, anst = 0;
    for (int i = 0; i < maxs; ++i) for (int j = 0; j < maxs; ++j) for (int k = 0; k < maxs; ++k)
        if (check(j, i, k) && check(i, j, 0))
        {
            int x = f[last][j][k] + calc(n, i), y = g[last][j][k] + getnum(i);
            if (ans > x) ans = x, anst = y;
            else if (ans == x && anst > y) anst = y;
        }
    printf("%d %d", anst, ans);
    return 0;
}