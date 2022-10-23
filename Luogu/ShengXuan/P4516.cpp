#include <cstdio>
#include <algorithm>
#include <ctype.h>
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
const int maxn = 1e5 + 100,maxk = 110;
struct node
{
    int to,next;
}E[maxn << 1];
int head[maxn];
inline void addE(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
const int mod = 1e9 + 7;
int n, k, size[maxn];
int f[maxn][maxk][2][2];
int g[maxk][2][2];
inline int add(int x,int y)
{
    int res = x + y;
    if(res >= mod) return res - mod;
    return res;
}
inline int mul(int x, int y) { return (1ll * x * y) % mod; }
void dfs(int u, int fa)
{
    size[u] = f[u][1][1][0] = f[u][0][0][0] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v,u);
        for (int i = 0; i <= size[u] && i <= k; ++i) 
        {
            g[i][0][0] = f[u][i][0][0], g[i][0][1] = f[u][i][0][1], g[i][1][0] = f[u][i][1][0], g[i][1][1] = f[u][i][1][1];
            f[u][i][0][0] = f[u][i][0][1] = f[u][i][1][0] = f[u][i][1][1] = 0;
        }
        for (int i = 0; i <= size[u] && i <= k; ++i)
            for (int j = 0; j <= size[v] && i + j <= k; ++j)
            {
                f[u][i + j][0][0] = add(f[u][i + j][0][0], mul(g[i][0][0], f[v][j][0][1]));
                f[u][i + j][0][1] = add(f[u][i + j][0][1], add(
                    mul(g[i][0][0], f[v][j][1][1]), 
                    mul(g[i][0][1], add(f[v][j][0][1], f[v][j][1][1]))));
                f[u][i + j][1][0] = add(f[u][i + j][1][0], mul(g[i][1][0], add(f[v][j][0][0], f[v][j][0][1])));
                f[u][i + j][1][1] = add(f[u][i + j][1][1], add(
                    mul(g[i][1][0], add(f[v][j][1][0], f[v][j][1][1])), 
                    mul(g[i][1][1], add(f[v][j][0][0], add(f[v][j][1][0], add(f[v][j][0][1], f[v][j][1][1]))))));
            }
        size[u] += size[v];
    }
}
int main()
{
    read(n),read(k);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), addE(a, b), addE(b, a);
    dfs(1, 0);
    printf("%d\n", add(f[1][k][1][1], f[1][k][0][1]));
    return 0;
}