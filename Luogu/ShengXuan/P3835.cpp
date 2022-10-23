#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstdlib>
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
const int magic = (1 << 15) - 1;
int n, root[maxn], L[maxn * 22], R[maxn * 22], sz[maxn * 22], pri[maxn * 22], val[maxn * 22], tot;
inline int rnd() { return rand() & magic; }
inline int newnode(int x = 0) { return val[++tot] = x, L[tot] = R[tot] = 0, pri[tot] = rnd(), sz[tot] = 1, tot; }
inline void pushup(int p) { sz[p] = sz[L[p]] + sz[R[p]] + 1; }
void split(int now, int k, int& x, int& y)
{
    if (!now) return (void)(x = y = 0);
    int p = newnode();
    L[p] = L[now], R[p] = R[now], val[p] = val[now];
    if (val[p] <= k) x = p, split(R[p], k, R[p], y);
    else y = p, split(L[p], k, x, L[p]);
    pushup(p);
}
int merge(int x, int y)
{
    if (!x || !y) return x + y;
    int p = newnode();
    if (pri[x] > pri[y]) val[p] = val[x], L[p] = L[x], R[p] = merge(R[x], y);
    else val[p] = val[y], R[p] = R[y], L[p] = merge(x, L[y]);
    return pushup(p), p;
}
int ins(int u, int k)
{
    int s, b;
    split(u, k, s, b);
    return merge(merge(s, newnode(k)), b);
}
int del(int u, int k)
{
    int s, m, b;
    split(u, k - 1, s, m), split(m, k, m, b), m = merge(L[m], R[m]);
    return merge(merge(s, m), b);
}
int askrnk(int& u, int k)
{
    int s, b, res;
    split(u, k - 1, s, b), res = sz[s] + 1, u = merge(s, b);
    return res;
}
int askbyrnk(int u, int k)
{
    if (k <= sz[L[u]]) return askbyrnk(L[u], k);
    if (k <= sz[L[u]] + 1) return val[u];
    return askbyrnk(R[u], k - sz[L[u]] - 1);
}
int findmax(int p) { while(R[p]) p = R[p]; return val[p]; }
int findmin(int p) { while(L[p]) p = L[p]; return val[p]; }
int pre(int& u, int k)
{
    int s, b, res;
    split(u, k - 1, s, b), res = findmax(s), u = merge(s, b);
    return res;
}
int nex(int& u, int k)
{
    int s, b, res;
    split(u, k, s, b), res = findmin(b), u = merge(s, b);
    return res;
}
void output(int p)
{
    if(!p) return;
    output(L[p]),printf("%d ",val[p]),output(R[p]);
}
int main()
{
    read(n);
    int now = 0;
    root[now] = ins(root[now], 1 << 31);
    root[now] = ins(root[now], 1 << 30);
    for (int i = 1, v, opt, x; i <= n; ++i)
    {
        read(v), read(opt), read(x);
        if (opt == 1) root[++now] = ins(root[v], x);
        else if (opt == 2) root[++now] = del(root[v], x);
        else if (opt == 3) root[++now] = root[v], printf("%d\n", askrnk(root[v], x) - 1);
        else if (opt == 4) root[++now] = root[v], printf("%d\n", askbyrnk(root[v], x + 1));
        else if (opt == 5) root[++now] = root[v], printf("%d\n", pre(root[v], x));
        else root[++now] = root[v], printf("%d\n", nex(root[v], x));
    }
    return 0;
}