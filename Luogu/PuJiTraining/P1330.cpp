#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
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
int n, m, color[maxn], tmp[2],ans,flag;
void dfs(int u,int col)
{
    if(flag) return;
    color[u] = col,tmp[col]++;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(color[v] == -1) dfs(v,col^1);
        else if(color[v] == col) {flag = 1;break;}
    }
}
int main()
{
    read(n),read(m);
    for (int i = 1, a, b; i <= m; ++i) read(a), read(b), add(a, b), add(b, a);
    for (int i = 1; i <= n; ++i) color[i] = -1;
    for (int i = 1; i <= n; ++i) if(color[i] == -1) 
    {
        dfs(i,0);
        if (flag) { puts("Impossible"); return 0; }
        ans += min(tmp[0], tmp[1]), tmp[0] = tmp[1] = 0;
    }
    printf("%d\n",ans);
    return 0;
}