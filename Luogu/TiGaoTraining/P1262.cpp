#include <cstdio>
#include <cstring>
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
const int maxn = 3100;
struct node
{
    int from, to, next;
} E[8100], F[8100];
int head[maxn];
inline void add(const int &x, const int &y)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].from = x;
    E[tot].next = head[x];
    head[x] = tot;
}
int hF[maxn];
inline void addF(const int &x, const int &y)
{
    static int tot = 0;
    F[++tot].to = y;
    F[tot].next = hF[x];
    hF[x] = tot;
}
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
}
int n, p, m;
int w[maxn];
int dfn[maxn], low[maxn], cnt;
int s[maxn], ins[maxn], top;
int W[maxn], minn[maxn], num[maxn], bel[maxn], tot;
void dfs(int u)
{
    dfn[u] = low[u] = ++cnt;
    s[++top] = u;
    ins[u] = 1;
    int v;
    for (int p = head[u]; p; p = E[p].next)
    {
        v = E[p].to;
        if (!dfn[v])
            dfs(v), low[u] = min(low[u], low[v]);
        else if (ins[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        int x;
        ++tot;
        W[tot] = w[u];
        minn[tot] = u;
        while ((x = s[top--]) != u)
        {
            num[tot]++;
            minn[tot] = min(x, minn[tot]);
            bel[x] = tot;
            ins[x] = 0;
            if (w[x])
                W[tot] = min(W[tot], w[x]);
        }
        bel[u] = tot;
        ins[u] = 0;
        num[tot]++;
    }
}
int in[maxn], vis[maxn];
int main()
{
    read(n);
    read(p);
    memset(w, 0x3f, sizeof(w));
    while (p--)
    {
        int x;
        read(x);
        read(w[x]);
    }
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int a, b;
        read(a);
        read(b);
        add(a, b);
        in[b]++;
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            dfs(i);
    int ans = 0, mina = 1 << 30;
    for (int i = 1; i <= n; ++i)
        if (in[i] == 0)
        {
            if (w[i] > 10000000)
            {
                mina = min(i, mina);
                break;
            }
            ans += w[i];
            for(int p = head[i];p;p=E[p].next)
            {
                int v = E[p].to;
                vis[bel[v]] = 1;
            }
        }
    for (int i = 1; i <= tot; ++i)
        if(vis[i])
            continue;
        else if (num[i] != 1 && W[i] > 10000000)
            mina = min(minn[i], mina);
        else
            ans += num[i] > 1 ? W[i] : 0;
    if (mina < 1000000)
    {
        puts("NO");
        printf("%d", mina);
        return 0;
    }
    puts("YES");
    printf("%d", ans);
    return 0;
}