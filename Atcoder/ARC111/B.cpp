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
const int maxn = 1e6 + 100;
int n, a[maxn], b[maxn], fa[maxn], siz[maxn],res;
bool tree[maxn], vis[maxn];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void unite(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y) return;
    fa[y] = x, tree[x] |= tree[y],siz[x] += siz[y];
}
inline void solve(int x) { x = find(x); if (!vis[x]) vis[x] = 1, res += siz[x] - !tree[x]; }
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]), read(b[i]), fa[a[i]] = a[i], fa[b[i]] = b[i], siz[a[i]] = siz[b[i]] = 1;
    for (int i = 1; i <= n; ++i)
    {
        int x = a[i], y = b[i];
        if (find(x) == find(y)) { tree[find(x)] = 1; continue; }
        unite(x, y);
    }
    for (int i = 1; i <= n; ++i) solve(a[i]), solve(b[i]);
    printf("%d\n", res);
    return 0;
}