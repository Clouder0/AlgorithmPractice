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
const int maxn = 2e5 + 100, maxm = maxn << 1;
struct node
{
    int from, to, next, directed;
} E[maxm];
int head[maxn], tot;
inline void add(const int &x, const int &y, const int &t)
{
    E[++tot].next = head[x], E[tot].from = x, E[tot].to = y, E[tot].directed = t, head[x] = tot;
}
int T, n, m;
int in[maxn];
int q[maxn], qh, qt, id[maxn], vis[maxn], cnt, ans;
inline void topo()
{
    qh = 1, qt = 0;
    for (int i = 1; i <= n; ++i) if (!in[i]) q[++qt] = i;
    while (qt >= qh)
    {
        if(ans) return;
        int u = q[qh++];
        id[u] = ++cnt, vis[u]++;
        //        printf("inq:%d\n",u);
        for (int p = head[u]; p; p = E[p].next)
        {
            if (!E[p].directed) continue;
            int v = E[p].to;
            if (--in[v] == 0) q[++qt] = v;
            if (in[v] < 0) ans = 1;
            //            printf("in:%d %d\n",v,in[v]);
        }
    }
    //    for(int i = 1;i<=n;++i) printf("%d %d %d\n",i,id[i],vis[i]);
}
int main()
{
    read(T);
    while (T--)
    {
        ans = tot = cnt = 0;
        read(n), read(m);
        for (int i = 1; i <= n; ++i)
            vis[i] = head[i] = 0, in[i] = 0;
        for (int i = 1; i <= m; ++i)
        {
            int t, a, b;
            read(t), read(a), read(b);
            add(a, b, t);
            if (t)
                in[b]++;
        }
        topo();
        if(ans) {puts("NO"); goto end;}
        for (int i = 1; i <= n; ++i) if (!id[i] || vis[i] != 1){puts("NO");goto end;}
        puts("YES");
        for (int i = 1; i <= m; ++i)
        {
            if (E[i].directed) printf("%d %d\n", E[i].from, E[i].to);
            else if (id[E[i].from] < id[E[i].to]) printf("%d %d\n", E[i].from, E[i].to);
            else printf("%d %d\n", E[i].to, E[i].from);
        }
        continue;
    end:;
    }
    return 0;
}