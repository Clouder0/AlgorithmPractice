#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL read()
{
    LL q = 0;
    char ch = ' ';
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') q = q * 10 + (LL)(ch - '0'), ch = getchar();
    return q;
}
#define RI register int
typedef double db;
const int N = 200005;
int tot, n, t, rt, mx, js;
int h[N], ne[N], to[N], fa[N], sz[N], vis[N], P[N];
LL w[N], p[N], q[N], l[N], dis[N], f[N];

int st[N], top;
db sl[N];
db slope(int x, int y) { return (db)(f[y] - f[x]) / (db)(dis[y] - dis[x]); }
void ins(int x)
{
    while (top >= 2 && sl[top - 1] <= slope(st[top], x))
        --top;
    st[++top] = x, sl[top] = -1e18, sl[top - 1] = slope(st[top - 1], st[top]);
}
int query(db num)
{
    int l = 1, r = top, mid, re;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (sl[mid] <= num)
            re = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    return st[re];
}

void getrt(int x, int SZ)
{
    sz[x] = 1;
    int bl = 0;
    for (RI i = h[x]; i; i = ne[i])
        if (!vis[to[i]])
            getrt(to[i], SZ), sz[x] += sz[to[i]], bl = max(bl, sz[to[i]]);
    bl = max(bl, SZ - sz[x]);
    if (bl <= mx)
        rt = x, mx = bl;
    printf("gr:%d %d\n",bl,rt);
}
void dfs(int x)
{
    P[++js] = x;
    for (RI i = h[x]; i; i = ne[i])
        if (!vis[to[i]])
            dfs(to[i]);
}
bool cmp(int x, int y) { return dis[x] - l[x] > dis[y] - l[y]; }
void work(int now, int SZ)
{
    printf("solve: %d %d\n",now,SZ);
    if (SZ == 1)
        return;
    mx = 1e9, getrt(now, SZ);
    int x = rt, kmx = mx;
    printf("%d %d %d\n",now,x,SZ);
    for (RI i = h[x]; i; i = ne[i])
    {
        printf("del:%d %d\n", to[i], sz[to[i]]);
        vis[to[i]] = 1, SZ -= sz[to[i]];
    }
    work(now, SZ);
    js = 0;
    for (RI i = h[x]; i; i = ne[i])
        dfs(to[i]);
    sort(P + 1, P + 1 + js, cmp);

    int j = x;
    top = 0;
    for (RI i = 1; i <= js; ++i)
    {
        int y = P[i];
        while (j != fa[now] && dis[j] >= dis[y] - l[y])
            ins(j), j = fa[j];
        if (top)
        {
            int k = query(p[y]);
            f[y] = min(f[y], f[k] + (dis[y] - dis[k]) * p[y] + q[y]);
        }
    }
    for (RI i = h[x]; i; i = ne[i])
        work(to[i], sz[to[i]]);
}

void add(int x, int y, int z) { to[++tot] = y, ne[tot] = h[x], h[x] = tot, w[tot] = z; }
void getdis(int x)
{
    for (RI i = h[x]; i; i = ne[i])
        dis[to[i]] = dis[x] + w[i], getdis(to[i]);
}
int main()
{
    int z;
    n = read(), t = read();
    for (RI i = 2; i <= n; ++i)
    {
        fa[i] = read(), z = read(), add(fa[i], i, z);
        p[i] = read(), q[i] = read(), l[i] = read(), f[i] = LLONG_MAX;
    }
    getdis(1);
    work(1, n);
    for (RI i = 2; i <= n; ++i)
        printf("%lld\n", f[i]);
    return 0;
}
