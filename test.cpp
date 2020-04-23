#include <cstdio>
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int N = 30005;
const int M = 60005;
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)

void add(int, int, int);
void dfs1(int);
void dfs2(int);
void build(int, int, int);
void update(int, int, int);
ll query(int, int);

int hed[N], nxt[M], to[M], val[M], id;
int dep[N], fa[N], siz[N], son[N], top[N], ttl[N], ltt[N], tot;
int vf[N];
int xs[N];
int sum[N << 2][10];
bool tag[N << 2][10];
int n, q;

int main()
{
    read(n), read(q);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u), read(v), read(w);
        add(u, v, w), add(v, u, w);
    }
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    build(1, 1, n);
    for (int i = 1; i <= q; ++i)
    {
        int type;
        read(type);
        int u, v;
        read(u), read(v);
        switch (type)
        {
        case 1:
            write(query(u, v)), EL;
            break;
        case 2:
            int w;
            read(w);
            update(u, v, w);
            break;
        }
    }
    return 0;
}

inline void add(int u, int v, int w)
{
    nxt[++id] = hed[u];
    hed[u] = id;
    to[id] = v;
    val[id] = w;
}
void dfs1(int u)
{
    siz[u] = 1;
    for (int i = hed[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v != fa[u])
        {
            dep[v] = dep[u] + 1;
            fa[v] = u;
            xs[v] = xs[u] ^ val[i];
            vf[v] = val[i];
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]])
            {
                son[u] = v;
            }
        }
    }
}
void dfs2(int u)
{
    ltt[ttl[u] = ++tot] = u;
    if (son[u])
    {
        top[son[u]] = top[u];
        dfs2(son[u]);
    }
    for (int i = hed[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v != fa[u] && v != son[u])
        {
            top[v] = v;
            dfs2(v);
        }
    }
}
inline void pushdown(int x, int xl, int xr, int bit)
{
    if (tag[x][bit])
    {
        int xm = (xl + xr) >> 1;
        sum[lc(x)][bit] = (xm - xl + 1) - sum[lc(x)][bit];
        sum[rc(x)][bit] = (xr - xm) - sum[rc(x)][bit];
        tag[lc(x)][bit] ^= 1;
        tag[rc(x)][bit] ^= 1;
        tag[x][bit] = false;
    }
}
inline void pushup(int x, int bit)
{
    sum[x][bit] = sum[lc(x)][bit] + sum[rc(x)][bit];
}
void update(int x, int xl, int xr, int bit, int ul, int ur)
{
    if (xl >= ul && xr <= ur)
    {
        sum[x][bit] = (xr - xl + 1) - sum[x][bit];
        tag[x][bit] ^= 1;
        return;
    }
    pushdown(x, xl, xr, bit);
    int xm = (xl + xr) >> 1;
    if (xm >= ul)
    {
        update(lc(x), xl, xm, bit, ul, ur);
    }
    if (xm < ur)
    {
        update(rc(x), xm + 1, xr, bit, ul, ur);
    }
    pushup(x, bit);
}
int query(int x, int xl, int xr, int bit, int ql, int qr)
{
    if (xl >= ql && xr <= qr)
    {
        return sum[x][bit];
    }
    pushdown(x, xl, xr, bit);
    int xm = (xl + xr) >> 1;
    int ans = 0;
    if (xm >= ql)
    {
        ans += query(lc(x), xl, xm, bit, ql, qr);
    }
    if (xm < qr)
    {
        ans += query(rc(x), xm + 1, xr, bit, ql, qr);
    }
    return ans;
}
void build(int x, int xl, int xr)
{
    if (xl == xr)
    {
        for (int i = 0; i < 10; ++i)
        {
            sum[x][i] = (xs[ltt[xl]] >> i) & 1;
        }
        return;
    }
    int xm = (xl + xr) >> 1;
    build(lc(x), xl, xm);
    build(rc(x), xm + 1, xr);
    for (int i = 0; i < 10; ++i)
    {
        pushup(x, i);
    }
}
void update(int u, int v, int w)
{
    int x = dep[u] < dep[v] ? v : u;
    for (int i = 0; i < 10; ++i)
    {
        if (((vf[x] ^ w) >> i) & 1)
        {
            update(1, 1, n, i, ttl[x], ttl[x] + siz[x] - 1);
        }
    }
    vf[x] = w;
}
ll query(int u, int v)
{
    int cnt[10];
    int siz = 0;
    for (int i = 0; i < 10; ++i)
    {
        cnt[i] = 0;
    }
    while (top[u] ^ top[v])
    {
        if (dep[top[u]] < dep[top[v]])
        {
            u ^= v ^= u ^= v;
        }
        siz += ttl[u] - ttl[top[u]] + 1;
        for (int i = 0; i < 10; ++i)
        {
            cnt[i] += query(1, 1, n, i, ttl[top[u]], ttl[u]);
        }
        u = fa[top[u]];
    }
    if (dep[u] < dep[v])
    {
        u ^= v ^= u ^= v;
    }
    siz += ttl[u] - ttl[v] + 1;
    for (int i = 0; i < 10; ++i)
    {
        cnt[i] += query(1, 1, n, i, ttl[v], ttl[u]);
    }
    ll ans = 0;
    for (int i = 0; i < 10; ++i)
    {
        ans += cnt[i] * (siz - cnt[i]) * 1ll * (1 << i);
    }
    return ans;
}
