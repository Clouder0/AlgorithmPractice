    #include <cstdio>
    #include <algorithm>
    #include <ctype.h>
    #include <cstring>
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
    const int maxn = 2e6 + 100;
    struct node
    {
        int to, next;
    } E[maxn];
    int head[maxn], tot;
    inline void add(const int& x, const int& y) { E[++tot].next = head[x], E[tot].to = y, head[x] = tot; }
    int n, dep[maxn], fa[maxn], siz[maxn], son[maxn], dis[maxn], ANS[maxn];
    char t[10];
    void dfs1(int u)
    {
        dis[u] ^= dis[fa[u]], siz[u] = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            dep[v] = dep[u] + 1, dfs1(v), siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    }
    int f[1 << 23];
    void update(int u)
    {
        f[dis[u]] = max(f[dis[u]],dep[u]);
        for (int p = head[u]; p; p = E[p].next) update(E[p].to);
    }
    void clean(int u)
    {
        f[dis[u]] = - (1 << 28);
        for (int p = head[u]; p; p = E[p].next) clean(E[p].to);
    }
    void getans(int u,int rt,int &tans)
    {
        tans = max(tans, f[dis[u]] + dep[u] - 2 * dep[rt]);
        for (int i = 0; i < 22; ++i) tans = max(tans, dep[u] + f[dis[u] ^ (1 << i)] - 2 * dep[rt]);
        for (int p = head[u]; p; p = E[p].next) getans(E[p].to, rt, tans);
    }
    void dfs2(int u, int keep)
    {
        for (int p = head[u]; p; p = E[p].next) 
        {
            int v = E[p].to;
            if (v == son[u]) continue;
            dfs2(v, 0),ANS[u] = max(ANS[u],ANS[v]); 
        }
        if (son[u]) dfs2(son[u], 1), ANS[u] = max(ANS[u], ANS[son[u]]);
        ANS[u] = max(ANS[u], f[dis[u]] - dep[u]);
        for (int i = 0; i < 22; ++i) ANS[u] = max(ANS[u], f[dis[u] ^ (1 << i)] - dep[u]);
        f[dis[u]] = max(f[dis[u]], dep[u]);
        for (int p = head[u], v; p; p = E[p].next)
        {
            if ((v = E[p].to) == son[u]) continue;
            getans(v, u, ANS[u]), update(v);
        }
        if(!keep)
        {
            f[dis[u]] = -(1 << 28);
            for (int p = head[u]; p; p = E[p].next) clean(E[p].to);
        }
    }
    int main()
    {
        read(n);
        for (int i = 2; i <= n; ++i) read(fa[i]), read(t + 1), add(fa[i], i), dis[i] = 1 << (t[1] - 'a');
        memset(f,~0x3f,sizeof(f));
        dfs1(1), dfs2(1, 1);
        for (int i = 1; i <= n; ++i) printf("%d ", ANS[i]);
        return 0;
    }