#include <cstdio>
#include <ctype.h>
#include <algorithm>
using namespace std;
#define DEBUG
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
const int maxn = 5e5 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], tot;
inline void add(int x, int y) { E[++tot].next = head[x], head[x] = tot, E[tot].to = y; }
int n, c[maxn];
int f[maxn], size[maxn], g[maxn];
bool cmp(const int &a,const int &b)
{
    return max(f[a],f[b] + 2 * size[a]) < max(f[b],f[a] + 2 * size[b]);
}
void dfs(int u,int fa)
{
    size[u] = 1,f[u] = c[u];
    int sonnum = 0;
    for (int p = head[u]; p; p = E[p].next) if (E[p].to != fa) dfs(E[p].to, u), size[u] += size[E[p].to];
    for (int p = head[u]; p; p = E[p].next) if (E[p].to != fa) g[++sonnum] = E[p].to;
    sort(g + 1, g + 1 + sonnum,cmp);
    int pretime = 0;
    for (int i = 1; i <= sonnum; ++i) f[u] = max(f[u], f[g[i]] + pretime + 1), pretime += 2 * size[g[i]];
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(c[i]);
    int tmp = c[1];
    c[1] = 0;
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dfs(1, 0);
//    for (int i = 1; i <= n; ++i) printf("%d\n", f[i]);
    printf("%d\n", max(f[1], (size[1] - 1) * 2 + tmp));
    return 0;
}