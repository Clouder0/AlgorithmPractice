#include <algorithm>
#include <cstdio>
const int maxn = 1e4, inf = 1 << 30;
struct node { int to, next, val; } E[maxn];
int head[maxn], cnt, n, m;
inline void add(int u, int v, int w) { E[++cnt].next = head[u], head[u] = cnt, E[cnt].to = v, E[cnt].val = w; }
int f[60000][10], bit[60000][10], bs[60000], pw[15];
int main()
{
    pw[0] = 1;
    for (int i = 1; i < 13; ++i) pw[i] = pw[i - 1] * 3;
    for (int i = 1; i < pw[10]; ++i)
    {
        int s = 0;
        for (int j = 0; j < 10; ++j) bit[i][j] = ((i / pw[j]) % 3), s += (bit[i][j] > 0);
        bs[i] = s;
    }
    while (scanf("%d%d", &n, &m) != EOF)
    {
        cnt = 0;
        for (int i = 0; i < n; ++i) head[i] = 0;
        for (int i = 1, a, b, c; i <= m; ++i)
            scanf("%d%d%d", &a, &b, &c), add(a - 1, b - 1, c), add(b - 1, a - 1, c);
        for (int i = 0; i < pw[n]; ++i)
            for (int j = 0; j < n; ++j) f[i][j] = inf;
        for (int i = 0; i < n; ++i) f[pw[i]][i] = 0;
        int res = inf;
        for (int i = 1; i < pw[n]; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (!bit[i][j]) continue;
                for (int p = head[j]; p; p = E[p].next)
                {
                    int last = E[p].to;
                    f[i][j] = std::min(f[i][j], f[i - pw[j]][last] + E[p].val);
                }
                if(bs[i] == n) res = std::min(res,f[i][j]);
            }
        }
        printf("%d\n", res == inf ? -1 : res);
    }
    return 0;
}