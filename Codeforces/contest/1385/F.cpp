#include <cstdio>
#include <set>
#include <queue>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
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
const int maxn = 2e5 + 100;
const int maxm = maxn * 2;
int T;
int n,k;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
set<int> E[maxn],G[maxn];
bool inq[maxn];
int main()
{
    read(T);
    while(T--)
    {
        while(!q.empty()) q.pop();
        read(n),read(k);
        for(int i = 1;i<=n;++i) E[i].clear(),G[i].clear(),inq[i] = 0;
        for (int i = 1; i < n; ++i) 
        {
            int a,b;
            read(a),read(b),E[a].insert(b),E[b].insert(a);
        }
        for (int i = 1; i <= n; ++i) if(E[i].size() == 1) G[*E[i].begin()].insert(i);
        for (int i = 1; i <= n; ++i) if(G[i].size() >= k) q.push(make_pair(G[i].size(),i)),inq[i] = 1;
        int ans = 0;
        while(!q.empty())
        {
            int u = q.top().second;
            q.pop();
            inq[u] = 0;
            while(G[u].size() >= k)
            {
                ++ans;
                for (int i = 1; i <= k; ++i)
                {
                    int v = *G[u].begin();
                    G[u].erase(v), E[u].erase(v), E[v].erase(u);
                    if(G[v].count(u)) G[v].erase(u);
                    if(E[v].size() == 1 && !inq[*E[v].begin()]) G[*E[v].begin()].insert(v),q.push(make_pair(G[*E[v].begin()].size(),*E[v].begin())),inq[*E[v].begin()] = 1;
                }
                if (E[u].size() == 1)
                {
                    int v = *E[u].begin();
                    G[v].insert(u);
                    if(G[v].size() >= k && !inq[v]) q.push(make_pair(G[v].size(),v)),inq[v] = 1;
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}