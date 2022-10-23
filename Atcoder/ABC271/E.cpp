#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast","-funroll-loops")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <cstdio>
#include <algorithm>
#include <map>
#include <queue>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
#define int long long
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
const int maxn = 5e5 + 100;
int n, m, k;
int A[maxn], B[maxn], C[maxn], E[maxn];
struct node
{
    int to, next, val, id;
} G[maxn];
int head[maxn], cnt;
inline void add(int u, int v, int w, int id)
{
    G[++cnt].next = head[u], head[u] = cnt, G[cnt].to = v, G[cnt].val = w, G[cnt].id = id;
}
struct status
{
    int u, dis, last_id;
    const bool operator<(const status& b) const
    {
        return !(this->dis < b.dis || (this->dis == b.dis && this->last_id < b.last_id));
    }
};
int vis[maxn];
map<int,int> mp[maxn];
signed main()
{
    read(n), read(m), read(k);
    for (int i = 1; i <= m; ++i) read(A[i]), read(B[i]), read(C[i]);
    for (int i = 1; i <= k; ++i) 
    {
        read(E[i]);
        add(A[E[i]], B[E[i]], C[E[i]], i);
    }
    priority_queue<status> q;
    q.push((status){1, 0, 0}), mp[1][0] = 0;
    while (!q.empty())
    {
        status now = q.top();
        q.pop();
        int u = now.u;
        map<int,int>::iterator it = mp[u].find(now.last_id);
        if (it == mp[u].end() || now.dis > it->second) continue;
        for (map<int, int>::iterator p = it; p != mp[u].end();)
            if (p->second > it->second)
                p = mp[u].erase(p);
            else ++p;
        for (int p = head[u]; p; p = G[p].next)
        {
            if (G[p].id < now.last_id) continue;
            int v = G[p].to;
            map<int, int>::iterator it = mp[v].find(G[p].id);
            if (it == mp[v].end() || (it->second > mp[u][now.last_id] + G[p].val))
            {
                mp[v][G[p].id] = mp[u][now.last_id] + G[p].val;
                q.push((status){v, mp[v][G[p].id], G[p].id});
            }
        }
    }
    if (mp[n].empty())
        puts("-1");
    else
    {
        int minn = 1ll << 60;
        for (map<int, int>::iterator it = mp[n].begin(); it != mp[n].end(); ++it) minn = min(minn, it->second);
        printf("%lld\n", minn);
    }
    return 0;
}