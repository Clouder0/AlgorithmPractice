#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
const int maxn = 5e4 + 100,maxm = 2 * maxn;
struct node
{
    int to,next,val;
}E[maxm];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,E[tot].val = val,head[x] = tot;
}
int n,m,len,tmp;
int f[maxn];
void dfs(int u,int fa)
{
    multiset<int> s;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v,u);
        if (f[v] + E[p].val >= len) ++tmp;
        else s.insert(f[v] + E[p].val);
    }
    while(!s.empty())
    {
        multiset<int>::iterator it = s.begin();
        int val = *it;
        s.erase(it);
        multiset<int>::iterator it2 = s.lower_bound(len - val);
        if (it2 == s.end()) f[u] = max(f[u],val);
        else s.erase(it2), ++tmp;
    }
}
inline bool check(int mid)
{
    for (int i = 1; i <= n; ++i) f[i] = 0;
    tmp = 0,len = mid;
    dfs(1,0);
    return tmp >= m;
}
int main()
{
    scanf("%d %d", &n, &m);
    int lensum = 0;
    for (int i = 1, a, b, c; i < n; ++i) scanf("%d %d %d", &a, &b, &c), add(a, b, c), add(b, a, c),lensum += c;
    int l = 1,r = lensum,mid,ans = -1;
    while(l <= r)
    {
        mid = l + r >> 1;
        if(check(mid)) l = mid + 1,ans = mid;
        else r = mid - 1;
    }
    printf("%d\n",ans);
    return 0;
}