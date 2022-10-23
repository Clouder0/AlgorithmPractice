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
const int maxn = 1100;
const int maxm = maxn * 2;
struct node
{
    int to,next;
}E[maxm];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int n;
int col[maxn],dep[maxn];
int cnt[maxn][2];
void dfs(int u,int fa)
{
    dep[u] = dep[fa] + 1;
    cnt[dep[u]][col[u]]++;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v,u);
    }
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(col[i]);
    for(int i = 1;i<n;++i)
    {
        int a,b;
        read(a),read(b),add(a,b),add(b,a);
    }
    //不加边都能过样例...
    dfs(1,0);
    for (int i = 1; i <= n; ++i) if(cnt[i][1] & 1) {puts("First");return 0;}
    puts("Second");
    return 0;
}