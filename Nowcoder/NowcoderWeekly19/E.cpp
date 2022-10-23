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
const int maxn = 2e6 + 100;
#define int long long
int n,m;
vector<int> G[maxn],id[maxn];
int fa[maxn],size[maxn];
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
    for (int i = 0; i <= m + 1; ++i) G[0].push_back(2), id[0].push_back(root);
    for (int i = 1; i <= n; ++i)
    {
        read(s + 1);
        G[i].push_back(2), id[i].push_back(root);
        for (int j = 1; j <= m; ++j)
            if (s[j] == '.') G[i].push_back(0), id[i].push_back(++cnt);
            else G[i].push_back(1), id[i].push_back(disable), ++num;
        G[i].push_back(2), id[i].push_back(root);
    }
    for (int i = 0; i <= m + 1; ++i) G[n + 1].push_back(2), id[n + 1].push_back(root);
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
    printf("%lld\n",ans + num);
    return 0;
}