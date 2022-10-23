#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using std::min;
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
const int maxn = 1e6;
struct node
{
    int to,next;
}E[maxn];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int n, m;
int dfn[maxn], low[maxn], ind;
int s[maxn], top, ins[maxn];
int sub[maxn], sccnum;
void tarjan(int u, int rt)
{
    dfn[u] = low[u] = ++ind, ins[u] = 1, s[++top] = u;
    int son = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(!dfn[v])
        {
            ++son, tarjan(v, rt), low[u] = min(low[u], low[v]);
            if (u == rt && son > 1) sub[u] = son;
            else if(low[v] >= dfn[u]) ++sub[u];
        }
        else if (ins[v]) low[u] = min(low[u], dfn[v]);
    }
    if (u == rt) --sub[u];
    if (dfn[u] == low[u])
    {
        ++sccnum, ins[u] = 0;
        while (s[top] != u) ins[s[top--]] = 0;
        --top;
    }
}
int main()
{
    read(n),read(m);
    for (int i = 1, u, v; i <= m; ++i) read(u), read(v), add(u, v), add(v, u);
    for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i, i);
//    printf("sccnum:%d\n",sccnum);
    for (int i = 1; i <= n; ++i) printf("%d ",sccnum + sub[i]);
    return 0;
}