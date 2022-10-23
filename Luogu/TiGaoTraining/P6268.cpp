#include <cstdio>
#include <algorithm>
#include <ctype.h>
#include <vector>
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
const int maxn = 5100;
int n, m,col[maxn],A[maxn],B[maxn];
vector<int> E[maxn];
void dfs(int u)
{
    for(vector<int>::iterator it = E[u].begin();it!=E[u].end();++it)
    {
        int v = *it;
        if(col[v] == -1)  col[v] = col[u] ^ 1,dfs(v);
    }
}
int match[maxn],vis[maxn];
bool dfs2(int u,int t)
{
    if(vis[u] == t) return 0;
    vis[u] = t;
    for(vector<int>::iterator it = E[u].begin();it!=E[u].end();++it)
    {
        int v = *it;
        if(!match[v] || dfs2(match[v],t)) return match[v] = u,1;
    }
    return 0;
}
int main()
{
    read(n), read(m);
    for (int i = 1, a, b; i <= m; ++i) read(a), read(b), ++a, ++b, E[a].push_back(b), E[b].push_back(a), A[i] = a, B[i] = b;
    for (int i = 1; i <= n; ++i) col[i] = -1;
    for (int i = 1; i <= n; ++i) if(col[i] == -1) dfs(i);
    for (int i = 1; i <= n; ++i) E[i].clear();
    for (int i = 1; i <= m; ++i) 
    {
        if (col[A[i]] > col[B[i]]) swap(A[i], B[i]);
        E[A[i]].push_back(B[i]);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) if(dfs2(i,i)) --ans;
    for (int i = 1; i <= n; ++i) if(col[i]) ++ans;
    printf("%d\n",ans);
    return 0;
}