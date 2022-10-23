#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <queue>
using namespace std;
const int bufSize = 1e6;
#define int long long
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc())
        ;
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
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
int n, m, L, s, t;
struct node
{
    int to, next, val;
} E[maxn * 3];
int head[maxn], oldhead[maxn], tot;
inline void add(const int& x, const int& y, const int& w)
{
    E[++tot].next = head[x], E[tot].to = y, E[tot].val = w, head[x] = tot;
}
int dis[maxn], vis[maxn];
int U[maxn], V[maxn], W[maxn];
void dij()
{
    priority_queue<pair<int, int>> q;
    for (int i = 1; i <= n; ++i) dis[i] = 1ll << 40, vis[i] = 0;
    dis[s] = 0;
    q.push(make_pair(-dis[s], s));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (dis[v] > dis[u] + E[p].val)
            {
                dis[v] = dis[u] + E[p].val;
                q.push(make_pair(-dis[v], v));
            }
        }
    }
}
signed main()
{
    read(n), read(m), read(L), read(s), read(t);
    ++s, ++t;
    for (int i = 1; i <= m; ++i)
    {
        read(U[i]), read(V[i]), read(W[i]);
        ++U[i], ++V[i];
        if (W[i] != 0) add(U[i], V[i], W[i]), add(V[i], U[i], W[i]);
    }
    dij();
    if (dis[t] < L)
    {
        puts("NO");
        return 0;
    }
    int l = 1, r = m, mid, ans = 0;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        int old = tot;
        for (int i = 1; i <= n; ++i) oldhead[i] = head[i];
        for (int i = 1; i <= mid; ++i)
            if (!W[i]) add(U[i], V[i], 1), add(V[i], U[i], 1);
        dij();
        if (dis[t] > L)
            l = mid + 1;
        else
            ans = mid, r = mid - 1;
        tot = old;
        for (int i = 1; i <= n; ++i) head[i] = oldhead[i];
    }
    if(ans == 0)
    {
        puts("NO");
        return 0;
    }
    for (int i = 1; i < ans; ++i)
        if (!W[i]) add(U[i], V[i], 1), add(V[i], U[i], 1);
    //    printf("ans%lld\n",ans);
    l = 1, r = L;
    int res = 1;
    while (l <= r)
    {
        int old = tot;
        for (int i = 1; i <= n; ++i) oldhead[i] = head[i];
        mid = (l + r) >> 1;
        add(U[ans], V[ans], mid);
        add(V[ans], U[ans], mid);
        dij();
        if (dis[t] >= L)
            res = mid, r = mid - 1;
        else
            l = mid + 1;
        tot = old;
        for (int i = 1; i <= n; ++i) head[i] = oldhead[i];
    }
    puts("YES");
    for (int i = 1; i <= m; ++i)
    {
        if (W[i])
            printf("%lld %lld %lld\n", U[i] - 1, V[i] - 1, W[i]);
        else
        {
            if (i < ans)
                printf("%lld %lld 1\n", U[i] - 1, V[i] - 1);
            else if (i == ans)
                printf("%lld %lld %lld\n", U[i] - 1, V[i] - 1, res);
            else
                printf("%lld %lld %lld\n", U[i] - 1, V[i] - 1, L + 1);
        }
    }
    return 0;
}