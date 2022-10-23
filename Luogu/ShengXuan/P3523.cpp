#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
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
const int maxn = 3e5 + 100;
struct node
{
    int to,next;
}E[maxn << 1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
const int inf = 1 << 30;
int n, m, d[maxn];
int f1[maxn], f2[maxn];
int L, R, MID, ANS, tot;
void dfs(int u,int fa)
{
    f1[u] = -inf, f2[u] = inf;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v,u);
        f1[u] = max(f1[u], f1[v] + 1);
        f2[u] = min(f2[u], f2[v] + 1);
    }
    if(d[u] && f2[u] > MID) f1[u] = max(0,f1[u]);
    else if(f1[u] + f2[u] <= MID) f1[u] = -inf;
    if(f1[u] == MID) f2[u] = 0,f1[u] = -inf,++tot;
}
bool check()
{
    tot = 0,dfs(1,0);
    if(f1[1] >= 0) ++tot;
    return tot <= m;
}
int main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(d[i]);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    L = 0, R = n;
    while (L <= R)
    {
        MID = L + R >> 1;
        if(check()) R = MID - 1,ANS = MID;
        else L = MID + 1;
    }
    printf("%d\n",ANS);
    return 0;
}