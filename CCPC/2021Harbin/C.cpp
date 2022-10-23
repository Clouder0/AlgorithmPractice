#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <map>
#include <set>
#define DEBUG
#define int long long
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc())
        ;
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e5 + 100;
int n, m, fa[maxn], c[maxn], leafnum;
struct node
{
    int to, next;
} E[maxn];
int head[maxn];
inline void add(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int minn[maxn];
/*
int f[maxn][maxn], minn[maxn];
void dfs(int u)
{
    if(c[u]) return;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        dfs(v);
        for (int j = 1; j <= m; ++j) f[u][j] += std::min(minn[v],f[v][j]);
        minn[u] += minn[v];
    }
    for (int j = 1; j <= m; ++j) minn[u] = std::min(minn[u], f[u][j] + 1);
}
*/
int addtag[maxn];
map<int, int> mp[maxn];
set<pair<int, int>> S[maxn];
void dfs2(int u)
{
    if (c[u]) return;
    int son = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        dfs2(v);
        if (!son || mp[v].size() > mp[son].size()) son = v;
        minn[u] += minn[v];
        addtag[u] += minn[v];
    }
    std::swap(mp[u], mp[son]);
    std::swap(S[u], S[son]);
    for (auto it = S[u].lower_bound(make_pair(minn[son] - addtag[son], 0)); it != S[u].end(); ++it)
        mp[u].erase(it->second);
    S[u].erase(S[u].lower_bound(make_pair(minn[son] - addtag[son], 0)), S[u].end());
    //    mp[u] = mp[son];
    addtag[u] += addtag[son];
    addtag[u] -= minn[son];
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == son) continue;
        for (map<int, int>::iterator it = mp[v].begin(); it != mp[v].end(); ++it)
        {
            map<int, int>::iterator cur = mp[u].find(it->first);
            if (cur == mp[u].end())
            {
                mp[u][it->first] = std::min(minn[v], it->second + addtag[v]) - minn[v] + minn[son] - addtag[son];
                S[u].insert(make_pair(mp[u][it->first], it->first));
                minn[u] = min(minn[u], addtag[u] + mp[u][it->first] + 1);
            }
            else
            {
                S[u].erase(make_pair(cur->second, cur->first));
                cur->second += min(minn[v], it->second + addtag[v]) - minn[v];
                S[u].insert(make_pair(cur->second, cur->first));
                minn[u] = min(minn[u], addtag[u] + cur->second + 1);
            }
        }
    }
    //    printf("minn[%lld]=%lld\n",u,minn[u]);
}
signed main()
{
    read(n);
    for (int i = 2; i <= n; ++i) read(fa[i]), add(fa[i], i);
    for (int i = 1; i <= n; ++i)
    {
        read(c[i]);
        m = std::max(m, c[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!c[i]) continue;
        //        for (int j = 0; j <= m; ++j) f[i][j] = n + 1;
        // f[i][c[i]] = 0;
        minn[i] = 1;
        mp[i][c[i]] = 0;
        S[i].insert(make_pair(0, c[i]));
    }
    // dfs(1);
    dfs2(1);
    //    for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) printf("f[%lld][%lld]=%lld\n",i,j,f[i][j]);
    //     for (int i = 1; i <= n; ++i)
    //         for (map<int, int>::iterator it = mp[i].begin(); it != mp[i].end(); ++it)
    //             printf("f[%lld][%lld]=%lld\n", i, it->first, it->second + addtag[i]);
    printf("%lld\n", minn[1]);
    return 0;
}
