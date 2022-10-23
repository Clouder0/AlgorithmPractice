#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
using namespace std;
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
const int maxn = 2e5 +100;
struct node
{
    int to,next;
}E[maxn];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int n, w[maxn], fa[maxn];
int H[maxn], cnt;
int root[maxn], tag[maxn * 20], maxx[maxn * 20], L[maxn * 20], R[maxn * 20], s[maxn * 20], top, ind;
inline int newnode() { return top ? s[top--] : ++ind; }
inline void clear(int x) { if (x) L[x] = R[x] = maxx[x] = 0, s[++top] = x; }
void merge(int& x, int y)
{
    if (!x || !y) return (void)(x += y);
    maxx[x] += maxx[y], merge(L[x], L[y]), merge(R[x], R[y]),clear(y);
}
void modify(int l,int r,int &p,int ll,int rr)
{
    if(!p) p = newnode();
    if(l >= ll && r <= rr) return (void)(maxx[p]++);
    int mid = l + r >> 1;
    if (ll <= mid) modify(l, mid, L[p], ll, rr);
    if (rr > mid) modify(mid + 1, r, R[p], ll, rr);
}
int ask(int l,int r,int p,int pos)
{
    if(!p) return 0;
    int mid = l + r >> 1;
    if (pos <= mid) return maxx[p] + ask(l, mid, L[p], pos);
    else return maxx[p] + ask(mid + 1, r, R[p], pos);
}
void dfs(int u)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        dfs(v), merge(root[u], root[v]);
    }
    int t = ask(1, cnt, root[u], w[u] + 1) + 1;
    if (ask(1, cnt, root[u], w[u]) >= t) return;
    int l = 1, r = w[u], mid, ans = -1;
    while(l <= r)
    {
        mid = l + r >> 1;
        if (ask(1, cnt, root[u], mid) < t) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    modify(1, cnt, root[u], ans, w[u]);
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(w[i]),H[++cnt] = w[i];
    std::sort(H + 1, H + 1 + cnt), cnt = std::unique(H + 1, H + 1 + cnt) - H - 1;
    for (int i = 1; i <= n; ++i) w[i] = std::lower_bound(H + 1, H + 1 + cnt, w[i]) - H;
    for (int i = 2; i <= n; ++i) read(fa[i]), add(fa[i], i);
    dfs(1);
    printf("%d\n", ask(1,cnt,root[1],1));
    return 0;
}