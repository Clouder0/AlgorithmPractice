#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctype.h>
using std::max; 
using std::min;
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
const int maxn = 60,maxm = 2100;
struct node
{
    int to,next,val;
}E[maxm];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,E[tot].val = val,head[x] = tot;
}
int n, m, size[maxn], v[maxn], w[maxn], num[maxn], leaf[maxn], f[maxn][maxn * 2][maxm], tmp[maxm];
void dfs(int u)
{
    if (leaf[u]) return (void)(num[u] = min(num[u], m / w[u]));
    num[u] = 1 << 30;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        dfs(v);
        num[u] = min(num[u], num[v] / E[p].val);
        w[u] += E[p].val * w[v];
    }
    num[u] = min(num[u], m / w[u]);
}
void dfs2(int u)
{
    if(!u)
    {
        for (int p = head[u]; p; p = E[p].next)
        {
            dfs2(E[p].to);
			for(int i = m ; i >= 0 ; i --)
				for(int j = 0 ; j <= i ; j ++)
                    f[0][0][i] = max(f[0][0][i], f[0][0][i - j] + f[E[p].to][0][j]);
        }
        return;
    }
    if(leaf[u])
    {
        for (int i = num[u]; i >= 0; i--) for (int j = i; j <= num[u]; j++) f[u][i][j * w[u]] = v[u] * (j - i);
        return;
    }
    for (int p = head[u]; p; p = E[p].next) dfs2(E[p].to);
    for (int i = num[u]; i >= 0; --i)
    {
        memset(tmp, ~0x3f, sizeof(tmp));
        tmp[0] = 0;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            for (int j = m; j >= 0; --j)
            {
                int t = -(1 << 30);
                for (int k = 0; k <= j; ++k) t = max(t, tmp[j - k] + f[v][i * E[p].val][k]);
                tmp[j] = t;
            }
        }
        for (int j = 0; j <= i; ++j)
            for (int k = 0; k <= m; ++k) f[u][j][k] = max(f[u][j][k], tmp[k] + v[u] * (i - j));
    }
}
int fa[maxn];
int main()
{
    read(n), read(m);
    memset(f, ~0x3f, sizeof(f));
    for (int i = 1, k, x, y; i <= n; ++i)
    {
        read(v[i]);
        char opt[10];
        read(opt + 1);
        if (opt[1] == 'B') read(w[i]), read(num[i]), leaf[i] = 1;
        else
        {
            read(k);
            while (k--) read(x), read(y), add(i, x, y), fa[x] = i;
        }
    }
    for (int i = 1; i <= n; ++i) if (!fa[i]) add(0, i, 1);
    for (int i = 0; i <= m; ++i) f[0][0][i] = 0;
    dfs(0), dfs2(0);
    printf("%d\n", f[0][0][m]);
    return 0;
}