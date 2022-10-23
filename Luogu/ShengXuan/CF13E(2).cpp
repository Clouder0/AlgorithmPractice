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
#define ls to[x][0]
#define rs to[x][1]
int n, m, k[maxn], to[maxn][2], fa[maxn], siz[maxn];
inline void pushup(int x) { siz[x] = siz[ls] + siz[rs] + 1; }
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
void splay(int x) { for (int f = fa[x]; !isroot(x); rotate(x), f = fa[x]) if (!isroot(f)) rotate(get(x) == get(f) ? f : x); }
int access(int x) { int p = 0; for (; x; p = x, x = fa[x]) splay(x), rs = p, pushup(x); return p; }
int findmin(int x) { while (ls) x = ls; return splay(x), x; }
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) { read(k[i]); if (i + k[i] <= n) fa[i] = i + k[i]; }
    for (int i = 1, opt, x, y; i <= m; ++i)
    {
        read(opt), read(x);
        if (opt == 1) y = access(x), printf("%d %d\n", findmin(y), siz[y]);
        else
        {
            read(y), access(x), splay(x), fa[ls] = 0, ls = 0;
            if (x + y <= n) fa[x] = x + y;
        }
    }
    return 0;
}