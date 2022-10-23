#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <queue>
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
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e5 + 100, maxm = 2e5 + 100;
int T, n;
struct node
{
    int to, next, val, cost;
} E[maxm];
int head[maxn], tot;
inline void add(const int& x, const int& y, const int& val, const int& cost) { E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, E[tot].cost = cost, head[x] = tot; }
long long S;
int sonleaf[maxn], fadis[maxn], facost[maxn];
void dfs(int u, int fa)
{
    sonleaf[u] = 0;
    int flag = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        facost[v] = E[p].cost, fadis[v] = E[p].val, dfs(v, u);
        sonleaf[u] += sonleaf[v];
        flag = 1;
    }
    if (!flag) sonleaf[u] = 1;
}
struct choice
{
    int w, times;
    bool operator<(const choice& b) const { return 1ll * (w - w / 2) * times < 1ll * (b.w - b.w / 2) * b.times; }
};
priority_queue<choice> q[2];
long long v[2][maxn * 33], num[2];
int main()
{
    read(T);
    while (T--)
    {
        read(n), read(S);
        tot = 0;
        for (int i = 1; i <= n; ++i) head[i] = 0;
        for (int i = 1; i < n; ++i)
        {
            int a, b, c, d;
            read(a), read(b), read(c), read(d);
            add(a, b, c, d), add(b, a, c, d);
        }
        dfs(1, 0);
        num[0] = num[1] = 0;
        long long now = 0;
        for (int i = 2; i <= n; ++i)
        {
            choice t;
            t.w = fadis[i], t.times = sonleaf[i];
            now += 1ll * fadis[i] * sonleaf[i];
            q[facost[i] - 1].push(t);
        }
        for (int i = 0; i <= 1; ++i)
            while (!q[i].empty())
            {
                choice t = q[i].top();
                q[i].pop();
                ++num[i], v[i][num[i]] = 1ll * (t.w - t.w / 2) * t.times + v[i][num[i] - 1];
                if (t.w /= 2) q[i].push(t);
            }
        long long need = now - S;
        int p = 0, ans = num[0] + num[1] * 2;
        for (int i = num[0]; i >= 0; --i)
        {
            while (p <= num[1] && v[0][i] + v[1][p] < need) ++p;
            if (p == num[1] + 1) break;
            ans = std::min(ans, i + 2 * p);
        }
        printf("%d\n", ans);
    }
    return 0;
}