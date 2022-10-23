#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
#define DEBUG
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
int n,m;
struct node
{
    int to,next;
}E[maxn];
int head[maxn],tot;
inline void add(int x,int y) { E[++tot].next = head[x],head[x] = tot,E[tot].to = y; }
int low[maxn],dfn[maxn],ind;
int ins[maxn],st[maxn],top;
int bel[maxn],cnt,siz[maxn];
void dfs(int u)
{
    dfn[u] = low[u] = ++ind;
    ins[u] = 1,st[++top] = u;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(!dfn[v]) dfs(v),low[u] = min(low[u],low[v]);
        else if(ins[v]) low[u] = min(low[u],dfn[v]);
    }
    if(low[u] == dfn[u])
    {
        ins[u] = 0, bel[u] = ++cnt, siz[cnt] = 1;
        while (st[top] != u) bel[st[top]] = cnt, ins[st[top--]] = 0, ++siz[cnt];
        --top;
    }
}
int in[maxn];
int A[maxn],B[maxn];
int main()
{
    read(n),read(m);
    for (int i = 1, a, b; i <= m; ++i) read(a), read(b), add(a, b),A[i] = a,B[i] = b;
    for (int i = 1; i <= n; ++i) if(!dfn[i]) dfs(i);
    for (int i = 1; i <= n; ++i) head[i] = 0;
    tot = 0;
    for (int i = 1; i <= m; ++i) if(bel[A[i]] != bel[B[i]]) add(bel[A[i]],bel[B[i]]),in[bel[B[i]]]++;
    int ans = 0;
    for (int i = 1; i <= cnt; ++i) if(in[i] == 0) ++ans;
    for (int i = 1; i <= cnt; ++i) 
    {
        if(siz[i] > 1 || in[i]) continue;
        for (int p = head[i]; p; p = E[p].next) if (in[E[p].to] == 1) goto end;
        --ans; break;
        end:;
    }
    printf("%.6f\n",1.0 - 1.0 * ans / n);
    return 0;
}