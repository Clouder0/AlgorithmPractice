#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctype.h>
const int bufSize = 1e6;
const int maxn = 5e4 + 100;
int K,n,m;
struct node
{
    int to,next;
}E[maxn];
int head[maxn],tot;
inline void add(const int &x,const int &y)
{
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
char s1[10],s2[10];
int dfn[maxn],low[maxn],cnt;
int st[maxn],top,ins[maxn];
int sccnum,bel[maxn];
void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    st[++top] = u,ins[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(!dfn[v]) tarjan(v),low[u] = std::min(low[u],low[v]);
        else if(ins[v]) low[u] = std::min(low[u],dfn[v]);
    }
    if(low[u] == dfn[u])
    {
        ++sccnum;
        while(st[top] != u) bel[st[top]] = sccnum,ins[st[top--]] = 0;
        bel[u] = sccnum,ins[u] = 0,--top;
    }
}
int main()
{
    scanf("%d", &K);
    while (K--)
    {
        memset(head, 0, sizeof(head)), tot = 0;
        memset(dfn, 0, sizeof(dfn)), memset(low, 0, sizeof(low)),memset(ins,0,sizeof(ins));
        cnt = top = sccnum = 0;
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= m; ++i)
        {
            scanf("%s %s", s1 + 1, s2 + 1);
            int u = (s1[1] == 'm') * n,v = (s2[1] == 'm') * n;
            int r = 0;
            for(int j = 2;;)
            {
                r = r * 10 + s1[j] - 48;
                if (s1[++j] == '\0') break;
            }
            u += r, r = 0;
            for (int j = 2;;)
            {
                r = r * 10 + s2[j] - 48;
                if (s2[++j] == '\0') break;
            }
            v += r;
            add(u + 2 * n, v), add(v + 2 * n, u);
        }
        for (int i = 1; i <= n; ++i) add(i + 2 * n, i + n), add(i + 3 * n, i), add(i, i + 3 * n), add(i + n, i + 2 * n);
        for (int i = 1; i <= 4 * n; ++i) if (!dfn[i]) tarjan(i);
        for (int i = 1; i <= 2 * n; ++i) if (bel[i] == bel[i + 2 * n]) goto fail;
        for (int i = 1; i <= n; ++i) if (bel[i] == bel[i + n]) goto fail;
        puts("GOOD");
        continue;
        fail:
        puts("BAD");
    }
    return 0;
}