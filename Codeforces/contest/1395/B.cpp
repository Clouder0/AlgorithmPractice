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
const int maxn = 110;
int n,m,sx,sy;
int vis[maxn][maxn];
void dfs(int x,int y)
{
    if(x > n || y > m) return;
    vis[x][y] = 1;
    printf("%d %d\n",x,y);
    for(int i = 1;i<=m;++i) if(!vis[x][i] && vis[x+1][i]) dfs(x,i);
    for(int i = 1;i<=m;++i) if(!vis[x][i]) dfs(x,i);
    if(!vis[x+1][y]) dfs(x + 1,y);
}
int main()
{
    read(n),read(m),read(sx),read(sy);
    vis[sx][sy] = 1;
    printf("%d %d\n",sx,sy);
    dfs(1,sy);
    return 0;
}