#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctype.h>
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
const int maxn = 110;
int T, n, school[maxn], home[maxn], match[maxn], vis[maxn];
vector<int> E[maxn];
bool dfs(int u,int tag)
{
    if (vis[u] == tag) return 0;
    vis[u] = tag;
    for (vector<int>::iterator it = E[u].begin(); it != E[u].end(); ++it)
    {
        int v = *it;
        if (!match[v] || dfs(match[v], tag)) return match[v] = u, 1;
    }
    return 0;
}
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        for (int i = 1; i <= n * 2; ++i) E[i].clear(),vis[i] = match[i] = 0;
        for (int i = 1; i <= n; ++i) read(school[i]);
        for (int i = 1; i <= n; ++i) read(home[i]), home[i] = school[i] ? home[i] : 0;
        for (int i = 1; i <= n; ++i) if(school[i] && !home[i]) E[i].push_back(i + n);
        for (int i = 1; i <= n; ++i) for (int j = 1, x; j <= n; ++j) 
        {
            read(x);
            if (x && school[j]) E[i].push_back(j + n);
        }
        for (int i = 1; i <= n; ++i) if (!home[i] && !dfs(i, i)) { puts("T_T"); goto end; }
        puts("^_^");
        end:;
    }
    return 0;
}