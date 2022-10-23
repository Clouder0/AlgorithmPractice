#include <cstdio>
const int mod = 1e9 + 7;
const int maxn = 1100;
const int maxnn = 3e6;

int n, m, a[maxn][maxn], id[maxn][maxn], tot;
struct node
{
    int to, nxt;
} E[maxnn];
int head[maxnn], cnt;
inline void add(const int& u, const int& v)
{
    //    printf("add %d %d\n",,v);
    E[++cnt].nxt = head[u], head[u] = cnt, E[cnt].to = v;
}
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int in[maxnn], out[maxnn], f[maxnn][5], q[maxnn], qh, qt;
signed main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) scanf("%d", a[i] + j), id[i][j] = ++tot;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                int nx = i + dx[k], ny = j + dy[k];
                if (nx <= 0 || nx > n || ny <= 0 || ny > m) continue;
                if (a[nx][ny] == a[i][j] + 1)
                {
                    in[id[nx][ny]]++;
                    out[id[i][j]]++;
                    add(id[i][j], id[nx][ny]);
                }
            }
        }
    qh = 1;
    for (int i = 1; i <= tot; ++i)
        if (!in[i]) q[++qt] = i, f[i][1] = 1;
    while (qt >= qh)
    {
        int u = q[qh++];
        for (int p = head[u]; p; p = E[p].nxt)
        {
            int v = E[p].to;
            f[v][2] = (f[v][2] + f[u][1]) % mod;
            f[v][3] = (f[v][3] + f[u][2]) % mod;
            f[v][4] = (((f[v][4] + f[u][3]) % mod) + f[u][4]) % mod;
            if (--in[v] == 0)
                q[++qt] = v;
        }
    }
    int res = 0;
    //    for(int i = 1;i<=tot;++i) for(int j = 1;j<=4;++j) printf("f[%d][%d]=%d\n",i,j,f[i][j]);
    for (int i = 1; i <= tot; ++i)
        if (out[i] == 0) res = (res + f[i][4]) % mod;
    printf("%d\n", res);
    return 0;
}