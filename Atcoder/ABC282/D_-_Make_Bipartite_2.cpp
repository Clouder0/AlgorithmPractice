#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
#define int long long
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
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
struct node
{
    int to, next;
} E[maxn];
int head[maxn], tot;
inline void add(const int& u, const int& v)
{
    E[++tot].next = head[u], E[tot].to = v, head[u] = tot;
}
int n, m;
int num[2];
int col[maxn];
int vis[maxn];
long long res;
void dfs(int u, int from)
{
    if(vis[u]) return;
    vis[u] = 1, ++num[col[u]];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == from) continue;
        if(col[v] == -1)
        {
            col[v] = col[u] ^ 1;
            dfs(v, u);
        }
        else if (col[v] == col[u])
        {
            puts("0");
            exit(0);
        }
    }
}
signed main()
{
    read(n), read(m);
    for (int i = 1, a, b; i <= m; ++i) read(a), read(b), add(a, b), add(b, a);
    for (int i = 1; i <= n; ++i) col[i] = -1;
    res = -m;
    long long presiz = 0;
    for (int i = 1; i <= n; ++i)
        if (col[i] == -1)
        {
            num[0] = num[1] = col[i] = 0;
            dfs(i, 0);
            res += num[0] * num[1];
            res += presiz * (num[0] + num[1]);
            presiz += num[0] + num[1];
        }
    printf("%lld\n", res);
    return 0;
}