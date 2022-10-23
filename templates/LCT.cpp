#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
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
#define ls to[x][0]
#define rs to[x][1]
const int maxn = 5e5 + 100;
int n, m, to[maxn][2], sum[maxn], val[maxn], fa[maxn], rev[maxn];
inline void pushup(int x) { sum[x] = sum[ls] ^ sum[rs] ^ val[x]; }
inline void pushdown(int x) { if (rev[x]) std::swap(ls, rs), rev[ls] ^= 1, rev[rs] ^= 1, rev[x] = 0; }
inline bool get(int x) { return to[fa[x]][1] == x; }
inline bool isroot(int x) { return to[fa[x]][0] != x && to[fa[x]][1] != x; }
void rotate(int x)
{
    int f = fa[x], ff = fa[f], k = get(x);
    if (!isroot(f)) to[ff][get(f)] = x;
    fa[to[x][k ^ 1]] = f, to[f][k] = to[x][k ^ 1];
    fa[x] = ff, fa[f] = x, to[x][k ^ 1] = f;
    pushup(f), pushup(x);
}
void update(int x) { if (!isroot(x)) update(fa[x]); pushdown(x); }
void splay(int x) { update(x); for (int f = fa[x]; !isroot(x); rotate(x), f = fa[x]) if (!isroot(f)) rotate(get(x) == get(f) ? f : x); }
int access(int x) { int p = 0; for (; x; p = x, x = fa[x]) splay(x), rs = p, pushup(x); return p; }
void makeroot(int x) { access(x), splay(x), rev[x] ^= 1; }
void link(int x, int y) { makeroot(x), splay(x), fa[x] = y; }
void cut(int x, int y) { makeroot(x), access(y), splay(y); if (!to[x][1] && to[y][0] == x) fa[x] = to[y][0] = 0; }
int find(int x) { access(x), splay(x); while (ls) pushdown(x), x = ls; return splay(x), x; }
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(val[i]);
    for (int i = 1, opt, x, y; i <= m; ++i)
    {
        read(opt), read(x), read(y);
        if (opt == 0) { makeroot(x), printf("%d\n", sum[access(y)]); }
        else if (opt == 1) { if (find(x) != find(y)) link(x, y); }
        else if(opt == 2) { if (find(x) == find(y)) cut(x, y); }
        else access(x), splay(x), val[x] = y, pushup(x);
    }
    return 0;
}