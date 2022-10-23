#include <cstdio>
#include <cstring>
template <typename T>
inline T max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
const int bufSize = 1000000;
inline char nc()
{
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 2e3 + 10;
struct node
{
    int to, next, val;
} E[maxn << 1];
int head[maxn];
inline void add(const int &x, const int &y, const int &val)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].next = head[x];
    E[tot].val = val;
    head[x] = tot;
}
int n, k;
long long f[maxn][maxn];
int size[maxn];
void dfs(int u, int fa)
{
    f[u][0] = f[u][1] = 0;
    size[u] = 1;
    int v;
    for (int p = head[u]; p; p = E[p].next)
    {
        v = E[p].to;
        if (v == fa)
            continue;
        dfs(v, u);
        int t = size[u];
        size[u] += size[v];
        for (int i = min(size[u],k); i >= 0; --i)
        {
            if(f[u][i] != -1)
                f[u][i] += f[v][0] + (long long)size[v] * (n - k - size[v]) * E[p].val;
            for (int j = max(i - t,1); j <= size[v] && j <= k; ++j)
            {
                if(f[u][i-j] == -1)
                    continue;
                f[u][i] = max(f[u][i], f[u][i - j] + f[v][j] + (long long)(j * (k - j) + (size[v] - j) * (n - k - size[v] + j)) * E[p].val);
            }
        }
    }
}
int main()
{
    memset(f,-1,sizeof(f));
    read(n);
    read(k);
    for (int i = 1; i < n; ++i)
    {
        int a, b, c;
        read(a);
        read(b);
        read(c);
        add(a, b, c);
        add(b, a, c);
    }
    dfs(1, 0);
    printf("%lld", f[1][k]);
    return 0;
}