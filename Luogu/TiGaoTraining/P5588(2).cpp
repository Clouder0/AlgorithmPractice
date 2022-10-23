#include <cstdio>
template <typename T>
inline void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 1e6 + 10;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int &x, const int &y)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].next = head[x];
    head[x] = tot;
}
int n;
int w[maxn];
int colorNum[maxn], size[maxn];
long long f1[maxn]; //颜色只在当前点出现时的答案
long long f2[maxn]; //f2[i] 颜色i在链上时的答案
int cnt[maxn];      //cnt[i] 颜色i在当前出现的次数
int pointNum[maxn], preSize[maxn];
void dfs(int u, int fa)
{
    size[u] = 1;
    int v;
    int has = 0, hasSon = 0;
    int beginColorNum = cnt[w[u]];
    for (int p = head[u]; p; p = E[p].next)
    {
        v = E[p].to;
        if (v == fa)
            continue;
        int temp = cnt[w[u]];
        dfs(v, u);
        f1[u] += (long long)size[u] * size[v];
        size[u] += size[v];
        if (cnt[w[u]] != temp)
            ++has, hasSon = v;
    }
    f1[u] += (long long)(n - size[u]) * size[u]; //父亲节点
    if (beginColorNum != 0 || cnt[w[u]] + 1 != colorNum[w[u]])
        ++has;
    ++cnt[w[u]];
    if (has == 1)
    {
        int t = hasSon ? n - size[hasSon] : size[u];
        if (pointNum[w[u]] == 0)
            preSize[w[u]] = t;
        else if (pointNum[w[u]] == 1)
            f2[w[u]] = (long long)t * preSize[w[u]];
        pointNum[w[u]]++;
    }
}
int lastPos[maxn]; //记录某个颜色最后出现的点，用于处理只出现一次的情况
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(w[i]), colorNum[w[i]]++, lastPos[w[i]] = i;
    int x, y;
    for (int i = 1; i < n; ++i)
    {
        read(x);
        read(y);
        add(x, y);
        add(y, x);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i)
    {
        if (colorNum[i] == 0)
            printf("%lld\n", (long long)n * (n - 1) >> 1);
        else if (colorNum[i] == 1)
            printf("%lld\n", f1[lastPos[i]]);
        else if (pointNum[i] == 2)
            printf("%lld\n", f2[i]);
        else
            puts("0");
    }
    return 0;
}