#include <cstdio>
#include <algorithm>
const int maxn = 1e5 + 100;
const int mod = 51061;
inline int add(int x, int y) { int t = x + y; return t >= mod ? t - mod : t; }
inline int mul(int x, int y) { unsigned int t = x * y; return t >= mod ? t % mod : t; }
#define ls to[x][0]
#define rs to[x][1]
int n, m, to[maxn][2], siz[maxn], sum[maxn], multag[maxn], addtag[maxn], val[maxn], rev[maxn], fa[maxn];
inline int get(int x) { return to[fa[x]][1] == x; }
inline int isroot(int x) { return to[fa[x]][0] != x && to[fa[x]][1] != x; }
inline void pushup(int x) { siz[x] = siz[ls] + siz[rs] + 1, sum[x] = add(add(sum[ls], sum[rs]), val[x]); }
inline void pushadd(int x, int k) { val[x] = add(val[x], k), sum[x] = add(sum[x], mul(siz[x], k)), addtag[x] = add(addtag[x], k); }
inline void pushmul(int x, int k) { val[x] = mul(val[x], k), sum[x] = mul(sum[x], k), multag[x] = mul(multag[x], k), addtag[x] = mul(addtag[x], k); }
inline void pushdown(int x)
{
    if (rev[x]) std::swap(ls, rs), rev[ls] ^= 1, rev[rs] ^= 1, rev[x] = 0;
    if (multag[x] != 1) pushmul(ls, multag[x]), pushmul(rs, multag[x]), multag[x] = 1;
    if (addtag[x]) pushadd(ls, addtag[x]), pushadd(rs, addtag[x]), addtag[x] = 0;
}
void rotate(int x)
{
    int f = fa[x], ff = fa[f], k = get(x);
    if (!isroot(f)) to[ff][get(f)] = x;
    fa[to[x][k ^ 1]] = f, to[f][k] = to[x][k ^ 1];
    fa[x] = ff, fa[f] = x, to[x][k ^ 1] = f;
    pushup(f), pushup(x);
}
void update(int x) { if (!isroot(x)) update(fa[x]); pushdown(x); }
void splay(int x)
{
    update(x);
    for (int f = fa[x]; !isroot(x); rotate(x), f = fa[x])
        if (!isroot(f)) rotate(get(x) == get(f) ? f : x);
}
void access(int x) { for (int p = 0; x; p = x, x = fa[x]) splay(x), rs = p, pushup(x); }
void makeroot(int x) { access(x), splay(x), rev[x] ^= 1; }
void link(int x, int y) { makeroot(x), fa[x] = y; }
void split(int x, int y) { makeroot(x), access(y), splay(y); }
void cut(int x, int y) { split(x, y), to[y][0] = fa[x] = 0; }
int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 1; i <= n; ++i) multag[i] = siz[i] = val[i] = 1;
    for (int i = 1, x, y; i < n; ++i) scanf("%d %d", &x, &y), link(x, y);
    for (int i = 1, a, b, c, d; i <= m; ++i)
    {
        static char s[10];
        scanf("%s %d %d", s + 1, &a, &b);
        if(s[1] == '+')  scanf("%d", &c), split(a, b), pushadd(b, c);
        else if(s[1] == '-') scanf("%d %d", &c, &d), cut(a, b), link(c, d);
        else if(s[1] == '*') scanf("%d", &c), split(a, b), pushmul(b, c);
        else split(a, b), printf("%d\n", sum[b]);
    }
    return 0;
}