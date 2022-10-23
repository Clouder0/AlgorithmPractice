#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctype.h>
using namespace std;
#define DEBUG
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
const int maxn = 3e5 + 100;
struct node
{
    int to, next, val;
} E[maxn << 1];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, head[x] = tot;
}
int n,k,ans;
int maxx[maxn][110], secx[maxn][110];
void dfs(int u, int fa)
{
    bool flag = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v, u);
        for (int i = 0; i <= k; ++i)
        {
            int t = maxx[v][i] + E[p].val;
            if (i) t = max(t, maxx[v][i - 1]);
            if (t > maxx[u][i]) secx[u][i] = maxx[u][i], maxx[u][i] = t;
            else if (t > secx[u][i]) secx[u][i] = t;
        }
        flag = 0;
    }
    if(flag) maxx[u][0] = 0;
    for (int i = 1; i <= k; ++i) maxx[u][i] = max(maxx[u][i - 1], maxx[u][i]), secx[u][i] = max(secx[u][i - 1], secx[u][i]);
    for (int i = 0; i <= k; ++i) ans = max(ans, maxx[u][i] + secx[u][k - i]);
}
int main()
{
    read(n),read(k);
    memset(maxx, ~0x3f, sizeof(maxx)), memset(secx, ~0x3f, sizeof(secx));
    ans = -1 << 30;
    for (int i = 1, a, b, c; i < n; ++i) read(a), read(b), read(c), add(a, b, -c), add(b, a, -c);
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) for(int j = 0;j<=k;++j) printf("%d %d %d %d\n",i,j,maxx[i][j],secx[i][j]);
    printf("%d\n",-ans);
    return 0;
}