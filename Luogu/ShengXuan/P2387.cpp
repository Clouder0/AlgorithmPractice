#include <cstdio>
#include <algorithm>
#include <cctype>
using std::max;
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
const int maxn = 2e5 + 100;
struct Edge
{
    int from, to, a, b;
} E[maxn];
bool cmp(const Edge& a, const Edge& b) { return a.a == b.a ? a.b < b.b : a.a < b.a; }
#define ls son[x][0]
#define rs son[x][1]
int n, m, fa[maxn], son[maxn][2], val[maxn], maxx[maxn], maxid[maxn], rev[maxn];
inline int get(int x) { return son[fa[x]][1] == x; }
inline int isroot(int x) { return son[fa[x]][0] != x && son[fa[x]][1] != x; }
inline void pushrev(int x) { std::swap(ls, rs), rev[x] ^= 1; }
inline void pushdown(int x) { if (!rev[x]) return; pushrev(ls), pushrev(rs), rev[x] = 0; }
inline void pushup(int x)
{
    maxx[x] = max(maxx[ls], maxx[rs]);
    maxx[x] = max(maxx[x], val[x]);
    if(maxx[x] > 0 && maxx[x] == val[x]) maxid[x] = x - n;
    else if (maxx[x] == maxx[ls]) maxid[x] = maxid[ls];
    else maxid[x] = maxid[rs];
}
void rotate(int x)
{
    int f = fa[x], ff = fa[f], k = get(x);
    if (!isroot(f)) son[ff][get(f)] = x;
    fa[son[x][k ^ 1]] = f, son[f][k] = son[x][k ^ 1], son[x][k ^ 1] = f, fa[f] = x, fa[x] = ff;
    pushup(f), pushup(x);
}
void update(int x) { if (!isroot(x)) update(fa[x]); pushdown(x); }
void splay(int x) { update(x); for (int f = fa[x]; !isroot(x); rotate(x), f = fa[x]) if (!isroot(f)) rotate(get(x) == get(f) ? f : x); }
void access(int x) { for (int p = 0; x; p = x, x = fa[x]) splay(x), rs = p, pushup(x); }
void makeroot(int x) { access(x), splay(x), pushrev(x); }
void link(int x, int y) { makeroot(x), splay(x), fa[x] = y; }
void link(int id) { link(E[id].from, id + n), link(id + n, E[id].to); }
void cut(int x, int y) { makeroot(x), access(y), splay(y), fa[x] = son[y][0] = 0; }
void cut(int id) { cut(E[id].from, E[id].to); }
int find(int x) { access(x), splay(x); while (ls) pushdown(x), x = ls; return splay(x), x; }
int findmax(int x, int y) { makeroot(x), access(y), splay(y); return maxid[y]; }
int main()
{
    read(n), read(m);
    for (int i = 1; i <= m; ++i) read(E[i].from), read(E[i].to), read(E[i].a), read(E[i].b);
    std::sort(E + 1, E + 1 + m, cmp);
    for (int i = 1; i <= m; ++i) val[i + n] = E[i].b, maxx[i + n] = E[i].b, maxid[i + n] = i;
    int res = 1 << 30;
    for (int i = 1; i <= m; ++i)
    {
        if (find(E[i].from) != find(E[i].to)) link(i);
        else
        {
            int id = findmax(E[i].from, E[i].to);
            if (E[id].b > E[i].b) cut(id), link(i);
        }
        if (find(1) == find(n)) makeroot(1), access(n), splay(n), res = std::min(res, E[i].a + E[maxid[n]].b);
    }
    if(res == (1 << 30)) puts("-1"); else printf("%d\n", res);
    return 0;
}