#include <cstdio>
#include <queue>
#include <cstring> 
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
const int maxn = 2e3 + 100;
const int maxm = 2e6 + 100;
const int inf = 1061109567;
int n,m;
char s[maxm];
bool mp[maxn][maxn];
int num[maxn][maxn];
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
int fa[maxm],cnt;
int find(int x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
inline void unite(int x,int y)
{
    x = find(x),y = find(y);
    if(x == y) return;
    fa[x] = y;
}
struct node
{
    int to,next;
}E[5*maxm];
int head[maxm];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int dis[maxn*maxn];
int main()
{
    read(n),read(m);
    int sx,sy,tx,ty;
    read(sx),read(sy),read(tx),read(ty);
    memset(dis,0x3f,sizeof(dis));
    for (int i = 1; i <= n; ++i) 
    {
        scanf("%s", s + 1);
        for (int j = 1; j <= m; ++j) if (s[j] == '.') mp[i][j] = 1; else mp[i][j] = 0;
    }
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) num[i][j] = ++cnt, fa[cnt] = cnt;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (!mp[i][j]) continue;
            for (int k = 0; k < 4; ++k)
            {
                int nx = i + dx[k], ny = j + dy[k];
                if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
                if(!mp[nx][ny]) continue;
                unite(num[i][j], num[nx][ny]);
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            for (int x = std::max(i - 2, 1); x <= i + 2 && x <= n; ++x)
            {
                for (int y = std::max(j - 2, 1); y <= j + 2 && y <= m; ++y)
                {
                    if(!mp[x][y]) continue;
                    if (find(num[x][y]) == find(num[i][j])) continue;
                    add(find(num[x][y]), find(num[i][j]));
                }
            }
        }
    }
    std::queue<int> q;
    q.push(find(num[sx][sy]));
    dis[find(num[sx][sy])] = 0;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if(dis[v] > dis[u] + 1) dis[v] = dis[u] + 1,q.push(v);
        }
    }
    if(dis[find(num[tx][ty])] < inf) printf("%d\n",dis[find(num[tx][ty])]);
    else puts("-1");
    return 0;
}