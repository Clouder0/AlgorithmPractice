#include <cstdio>
#include <algorithm>
#include <ctype.h>
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
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template <typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 4e5 + 100;
const int maxm = maxn * 3;
int T, n;
int a[2][maxn];
int vis[maxn];
struct node
{
    int to, next, val;
} E[maxm];
int head[maxn], tot;
inline void add(const int &x, const int &y, const int &val)
{
    E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, head[x] = tot;
}
int col[maxn];
bool flag;
int s[2][maxn],stop[2];
void dfs(int u)
{
    s[col[u]][++stop[col[u]]] = u;
    if (flag) return;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (E[p].val)
        {
            if (col[v] == -1) col[v] = col[u] ^ 1, dfs(v);
            else if (col[v] == col[u]) flag = 1;
        }
        else if (E[p].val == 0)
        {
            if (col[v] == -1) col[v] = col[u], dfs(v);
            else if (col[v] != col[u]) flag = 1;
        }
        if (flag) return;
    }
}
int visall[maxn],ans;
int anss[maxn],atop;
int main()
{
    read(T);
    while (T--)
    {
//        printf("T:%d\n",T);
        read(n);
        for (int i = 1; i <= n * 2; ++i) col[i] = -1, head[i] = 0, vis[i] = 0, visall[i] = 0;
        atop = tot = flag = 0;
        for (int i = 1; i <= n; ++i) read(a[0][i]), visall[a[0][i]]++;
        for (int i = 1; i <= n; ++i) read(a[1][i]), visall[a[1][i]]++;
        for (int i = 1; i <= n; ++i)
            if (visall[i] != 2)
            {
                puts("-1");
                goto end;
            }
        for (int i = 1; i <= n; ++i)
        {
            if (vis[a[0][i]]) add(vis[a[0][i]], i, 1), add(i, vis[a[0][i]], 1);
            else vis[a[0][i]] = i;
        }
        for (int i = 1; i <= n; ++i)
        {
            if (vis[a[1][i]] == 0) vis[a[1][i]] = i + n;
            else if (vis[a[1][i]] <= n) add(vis[a[1][i]], i, 0), add(i, vis[a[1][i]], 0);
            else if (vis[a[1][i]] > n) add(vis[a[1][i]] - n, i, 1), add(i, vis[a[1][i]] - n, 1);
        }
        for(int i = 1;i<=n;++i) if(col[i] == -1)
        {
            stop[0] = stop[1] = 0;
            col[i] = 0;
            dfs(i);
            if (flag){printf("-1\n");goto end;}
            if(stop[0] < stop[1]) while(stop[0]) anss[++atop] = s[0][stop[0]--];
            else while(stop[1]) anss[++atop] = s[1][stop[1]--];
        }
//        col[1] = 0, dfs(1);

  //      printf("col:\n");
   //     for(int i = 1;i<=n;++i) printf("%d ",col[i]);
    //    putchar('\n');
        printf("%d\n", atop);
        while(atop) printf("%d ",anss[atop--]);
        putchar('\n');
    end:;
    }
    return 0;
}