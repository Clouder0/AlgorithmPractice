#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cstring>
const int maxn = 2e6 + 100;
const int magic = (1 << 15) - 1;
int n, pri[maxn], L[maxn], R[maxn], val[maxn], sz[maxn], tot, root, bin[maxn], bintop;
inline int rnd() { return rand() & magic; }
inline int newnode(int v = 0)
{
    int t = bintop ? bin[bintop--] : ++tot;
    return sz[t] = 1, val[t] = v, pri[t] = rnd(), t;
}
inline void clear(int x) { L[x] = R[x] = val[x] = sz[x] = 0, bin[++bintop] = x; }
inline void pushup(int p) { sz[p] = sz[L[p]] + sz[R[p]] + 1; }
void split(int now, int k, int& x, int& y)
{
    if (!now) return (void)(x = y = 0);
    if (val[now] <= k) x = now, split(R[now], k, R[now], y);
    else y = now, split(L[now], k, x, L[now]);
    pushup(now);
}
int merge(int x, int y)
{
    if (!x || !y) return x + y;
    if (pri[x] > pri[y]) return R[x] = merge(R[x], y), pushup(x), x;
    return L[y] = merge(x, L[y]), pushup(y), y;
}
int findmin(int u) { int p = u; while (L[p]) p = L[p]; return val[p]; }
int findmax(int u) { int p = u; while (R[p]) p = R[p]; return val[p]; }
void ins(int& u, int k)
{
    int small, big;
    split(u, k, small, big), u = merge(merge(small, newnode(k)), big);
}
void del(int& u, int k)
{
    int small, big, mid;
    split(u, k - 1, small, big), split(big, k, mid, big);
    if (mid) { int t = mid; mid = merge(L[mid], R[mid]), clear(t); }
    u = merge(merge(small, mid), big);
}
int getRnk(int& u, int k)
{
    int small, big, res;
    split(u, k - 1, small, big), res = sz[small] + 1, u = merge(small, big);
    return res;
}
int getByRnk(int u,int k)
{
    int p = u;
    while(p)
    {
        if (k <= sz[L[p]]) { p = L[p]; continue; }
        k -= sz[L[p]] + 1;
        if (k <= 0) return val[p];
        p = R[p];
    }
    return 0;
}
int pre(int& u, int k)
{
    int small, big, res;
    split(u, k - 1, small, big), res = findmax(small), u = merge(small, big);
    return res;
}
int nex(int& u, int k)
{
    int small, big, res;
    split(u, k, small, big), res = findmin(big), u = merge(small, big);
    return res;
}
int main()
{
    srand(time(0));
    scanf("%d", &n);
    int root = 0;
    for (int i = 1, opt, x; i <= n; ++i)
    {
        scanf("%d %d",&opt,&x);
        if (opt == 1) ins(root, x);
        else if(opt == 2) del(root,x);
        else if(opt == 3) printf("%d\n",getRnk(root,x));
        else if(opt == 4) printf("%d\n",getByRnk(root,x));
        else if(opt == 5) printf("%d\n",pre(root,x));
        else printf("%d\n",nex(root,x));
    }
    return 0;
}