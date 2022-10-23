#include <cstdio>
#include <vector>
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
inline void read(char *s)
{
    static char c;
    for (; c != '.' && c != '#'; c = nc());
    for (; c == '.' || c == '#'; c = nc()) *s++ = c;
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
const int maxn = 5e3 + 100;
const int maxm = 2e6 + 100;
int n,m;
int G[maxn][maxn],id[maxn][maxn];
int fa[maxm],size[maxm];
int find(const int &x){return fa[x] == x ? x : fa[x] = find(fa[x]);}
inline void merge(int x,int y)
{
    x = find(x),y = find(y);
    if(x == y) return;
    fa[y] = x,size[x] += size[y],size[y] = 0;
}
char s[maxn];
int cnt,root,disable,num;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
signed main()
{
    read(n),read(m);
    root = ++cnt,disable = ++cnt;
    for (int i = 0; i <= m + 1; ++i) G[0][i] = G[n + 1][i] = 2, id[0][i] = id[n + 1][i] = root;
    for (int i = 1; i <= n; ++i)
    {
        read(s + 1);
        G[i][0] = G[i][m + 1] = 2, id[i][0] = id[i][m + 1] = root;
        for (int j = 1; j <= m; ++j)
            if (s[j] == '.') G[i][j] = 0, id[i][j] = ++cnt;
            else G[i][j] = 1, id[i][j] = disable, ++num;
    }
    for (int i = 1; i <= cnt; ++i) fa[i] = i, size[i] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (G[i][j] == 0)
            {
                for (int k = 0; k < 3; ++k)
                {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (G[nx][ny] != 1) merge(id[nx][ny], id[i][j]);
                }
            }
        }
    }
    int ans = 0;
    root = find(root);
    for (int i = 1; i <= cnt; ++i)
    {
        if(i == root || i == disable || i != find(i)) continue;
        ans += size[i];
    }
    printf("%d\n",ans + num);
    return 0;
}