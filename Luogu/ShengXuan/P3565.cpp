#include <cstdio>
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
const int maxn = 5100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int n, cnt[maxn], dep[maxn], maxdep;
long long ans, one[maxn], two[maxn];
void dfs(int u,int fa)
{
    maxdep = max(maxdep, dep[u] = dep[fa] + 1);
    cnt[dep[u]]++;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs(v, u);
    }
}
int main()
{
    read(n);
    for (int i = 1,a,b; i < n; ++i) read(a),read(b),add(a,b),add(b,a);
    for (int u = 1; u <= n; ++u) 
    {
        dep[u] = 0;
        for (int i = 1; i <= n; ++i) one[i] = two[i] = 0;
        for (int p = head[u]; p; p = E[p].next) 
        {
            int v = E[p].to;
            for (int i = 1; i <= maxdep; ++i) cnt[i] = 0;
            dfs(v, u);
            for (int i = 1; i <= maxdep; ++i) ans += 1ll * cnt[i] * two[i];
            for (int i = 1; i <= maxdep; ++i) two[i] += 1ll * one[i] * cnt[i];
            for (int i = 1; i <= maxdep; ++i) one[i] += cnt[i];
        }
    }
    printf("%lld\n", ans);
    return 0;
}