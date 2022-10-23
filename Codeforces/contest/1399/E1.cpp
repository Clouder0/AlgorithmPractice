#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <queue>

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
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e5 + 100;
const int maxm = 2e5 + 100;
int T, n;
struct node
{
    int to, next, val;
} E[maxm];
int head[maxn], tot;
inline void add(const int& x, const int& y, const int& val) { E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, head[x] = tot; }
long long S;
int sonleaf[maxn], fadis[maxn];
void dfs(int u, int fa)
{
    sonleaf[u] = 0;
    int flag = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        fadis[v] = E[p].val, dfs(v, u);
        sonleaf[u] += sonleaf[v];
        flag = 1;
    }
    if (!flag) sonleaf[u] = 1;
}
struct choice
{
    int w, times;
    bool operator<(const choice& b) const
    {
        return 1ll * (w - w / 2) * times < 1ll * (b.w - b.w / 2) * b.times;
    }
};
priority_queue<choice> q;
int main()
{
    read(T);
    while (T--)
    {
        tot = 0;
        read(n);
        for (int i = 1; i <= n; ++i) head[i] = 0;
        read(S);
        for (int i = 1; i < n; ++i)
        {
            int a, b, c;
            read(a), read(b), read(c);
            add(a, b, c), add(b, a, c);
        }
        dfs(1, 0);
        while (!q.empty()) q.pop();
        long long now = 0;
        for (int i = 2; i <= n; ++i)
        {
            choice t;
            t.w = fadis[i], t.times = sonleaf[i];
            now += 1ll * fadis[i] * sonleaf[i];
            q.push(t);
        }
        int opt = 0;
        while (now > S)
        {
            choice t = q.top();
            q.pop();
            now -= 1ll * (t.w - t.w / 2) * t.times;
            t.w /= 2;
            if (t.w) q.push(t);
            ++opt;
        }
        printf("%d\n", opt);
    }
    return 0;
}