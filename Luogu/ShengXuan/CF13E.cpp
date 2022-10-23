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
const int maxn = 1e6 + 100;
#define ls to[x][0]
#define rs to[x][1]
int n, m, k[maxn], to[maxn][2], fa[maxn], siz[maxn], rev[maxn];
inline void pushup(int x) { siz[x] = siz[ls] + siz[rs] + 1; }
inline void pushdown(int x)
{
    if (!rev[x]) return;
    std::swap(ls, rs), rev[ls] ^= 1, rev[rs] ^= 1, rev[x] = 0;
}
inline bool get(int x) { return to[fa[x]][1] == x; }
inline bool isroot(int x) { return to[fa[x]][0] != x && to[fa[x]][1] != x; }
void rotate(int x)
{
    int f = fa[x], ff = fa[f], k = get(x);
    if (!isroot(f)) to[ff][get(f)] = x;
    fa[to[x][k ^ 1]] = f, to[f][k] = to[x][k ^ 1];
    to[x][k ^ 1] = f, fa[f] = x, fa[x] = ff;
    pushup(f), pushup(x);
}
void update(int x) { if (!isroot(x)) update(fa[x]); pushdown(x); }
void splay(int x)
{
    update(x);
    for (int f = fa[x]; !isroot(x); rotate(x), f = fa[x]) if (!isroot(f)) rotate(get(x) == get(f) ? f : x);
}
int access(int x) { int p = 0; for (; x; p = x, x = fa[x]) splay(x), rs = p, pushup(x); return p; }
void makeroot(int x) { access(x), splay(x), rev[x] ^= 1; }
void link(int x, int y) { makeroot(x), fa[x] = y; }
void cut(int x, int y) { makeroot(x), access(y), splay(y), to[y][0] = fa[x] = 0; }
int nex(int x)
{
    pushdown(x); if (rs) x = rs;
    again:
    pushdown(x); if (ls) { x = ls; goto again; }
    return x;
}
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) { read(k[i]); if (i + k[i] <= n) fa[i] = i + k[i]; else fa[i] = n + 1; }
    for (int i = 1, opt, x, y; i <= m; ++i)
    {
        read(opt), read(x);
        if (opt == 1) makeroot(n + 1), access(x), splay(n + 1), printf("%d %d\n", nex(n + 1), siz[n + 1] - 1);
        else
        {
            read(y);
            if (x + k[x] <= n) cut(x, x + k[x]); else cut(x, n + 1);
            k[x] = y;
            if (x + k[x] <= n) link(x, x + k[x]); else link(x, n + 1);
        }
    }
    return 0;
}