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
int n, m, a[maxn], last[maxn], sum[maxn], ans[maxn];
inline void add(int x, int k) { for (; x > 0; x -= x & -x) sum[x] += k; }
inline int ask(int x) { int res = 0; for (; x <= n; x += x & -x) res += sum[x]; return res; }
struct node
{
    int l, id, next;
} Q[maxn];
int head[maxn],tot;
inline void addq(int l, int r, int id) { Q[++tot].l = l, Q[tot].next = head[r], head[r] = tot, Q[tot].id = id; }
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    read(m);
    for (int i = 1, l, r; i <= m; ++i) read(l), read(r), addq(l, r, i);
    for (int i = 1; i <= n; ++i)
    {
        if (last[a[i]]) add(last[a[i]], -1);
        add(last[a[i]] = i, 1);
        for (int p = head[i]; p; p = Q[p].next) ans[Q[p].id] = ask(Q[p].l);
    }
    for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
    return 0;
}