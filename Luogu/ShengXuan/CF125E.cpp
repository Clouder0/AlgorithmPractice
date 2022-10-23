#include <cstdio>
#include <algorithm>
#include <ctype.h>
#include <set>
#include <vector>
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
const int maxn = 2e5 + 100;
struct node
{
    int u, v, w, id;
} E[maxn];
struct Enode
{
    int to, next, w, id;
} G[maxn];
int head[maxn], tot;
inline void add(int x, int y, int w,int id)
{
    G[++tot].to = y, G[tot].next = head[x], head[x] = tot, G[tot].w = w,G[tot].id = id;
}
int n, m, k, mid;
int fa[maxn],size[maxn];
int find(int x){return fa[x] == x ? x : fa[x] = find(fa[x]);}
inline void unite(int x,int y)
{
    x = find(x),y = find(y);
    if(x == y) return;
    if (size[x] < size[y]) std::swap(x, y);
    fa[y] = x, size[x] += size[y];
}
bool cmp(const node &a,const node &b)
{
    if(a.w != b.w) return a.w < b.w;
    return a.u < b.u;
}
inline void init() { for (int i = 1; i <= n; ++i) fa[i] = i,size[i] = 1; }
bool check()
{
    init();
    int num = 0;
    for (int i = 1; i <= m; ++i) if (E[i].u > 1) unite(E[i].u, E[i].v); else ++num;
    if(num < k) return 0;
    num = 0;
    for (int i = 2; i <= n; ++i) num += (find(i) == i);
    if(num > k) return 0;
    for (int i = 1; i <= m; ++i) if(E[i].u == 1) unite(E[i].u,E[i].v);
    num = 0;
    for (int i = 1; i <= n; ++i) num += (find(i) == i);
    return num == 1;
}
bool vis[maxn];
int val[maxn],id[maxn];
std::set<int> S;
void dfs(int u,int fat)
{
    fa[u] = fa[fat];
    for (int p = head[u]; p; p = G[p].next)
    {
        int v = G[p].to;
        if(v == fat) continue;
        dfs(v,u);
    }
}
int main()
{
    read(n), read(m), read(k);
    int maxx = -(1<<30);
    for (int i = 1; i <= m; ++i) read(E[i].u), read(E[i].v), read(E[i].w), E[i].id = i, maxx = std::max(maxx, E[i].w);
    for (int i = 1; i <= m; ++i) if (E[i].u > E[i].v) std::swap(E[i].u, E[i].v);
    if (!check()) { puts("-1"); return 0; }
    int l = -maxx, r = maxx, mid, ans = -1, edgenum, onenum;
    while (l <= r)
    {
        mid = l + r >> 1;
        edgenum = onenum = 0;
        init();
        for (int i = 1; i <= m; ++i) if (E[i].u == 1) E[i].w += mid;
        std::sort(E + 1, E + 1 + m, cmp);
        for (int i = 1; edgenum < n - 1 && i <= m; ++i) 
        {
            if (find(E[i].u) == find(E[i].v)) continue;
            unite(E[i].u, E[i].v);
            ++edgenum, onenum += (E[i].u == 1);
        }
        for (int i = 1; i <= m; ++i) if(E[i].u == 1) E[i].w -= mid;
        if(onenum >= k) ans = mid,l = mid + 1;
        else r = mid - 1;
    }
    init(), onenum = 0;
    for (int i = 1; i <= m; ++i) if (E[i].u == 1) E[i].w += ans;
    std::sort(E + 1,E + 1 + m,cmp);
    for (int i = 1; i <= m; ++i) 
    {
        if (find(E[i].u) == find(E[i].v)) continue;
        unite(E[i].u, E[i].v);
        vis[i] = 1,onenum += (E[i].u == 1),S.insert(E[i].id);
        add(E[i].u, E[i].v, E[i].w, E[i].id);
        add(E[i].v, E[i].u, E[i].w, E[i].id);
    }
    for (int p = head[1]; p; p = G[p].next)
    {
        int v = G[p].to;
        val[v] = G[p].w,id[v] = G[p].id;
        fa[1] = v, dfs(v, 1);
    }
    for (int i = 1; i <= m && onenum > k; ++i) 
    {
        if(E[i].u != 1 && !vis[i])
        {
            if(find(E[i].u) == find(E[i].v)) continue;
            int u = find(E[i].u),v = find(E[i].v);
            if (val[u] == E[i].w) fa[u] = v, --onenum, S.insert(E[i].id), S.erase(id[u]);
            else if (val[v] == E[i].w) fa[v] = u, --onenum, S.insert(E[i].id), S.erase(id[v]);
        }
    }
    if(onenum == k) 
    {
        printf("%d\n",n - 1);
        for(std::set<int>::iterator it = S.begin();it!=S.end();++it) printf("%d ",*it);
    }
    else puts("-1");
    return 0;
}