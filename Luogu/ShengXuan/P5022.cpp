#pragma GCC target("avx")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
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
#include <cstring>
#include <algorithm>
#include <queue>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 5100;
struct node
{
    int to,next;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x];
    E[tot].to = y;
    head[x] = tot;
}
int n,m;
namespace D
{
    int vis[maxn];
    void dfs(int u)
    {
        printf("%d ", u);
        vis[u] = 1;
        int v;
        std::priority_queue<int,std::vector<int>,std::greater<int> > q;
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            if(vis[v])
                continue;
            q.push(v);
        }
        while(!q.empty())
        {
            v = q.top();
            q.pop();
            dfs(v);
        }
    }
    void solve()
    {
        dfs(1);
    }
}
namespace C
{
    int vis[maxn];
    int s[maxn],tot;
    int ans[maxn];
    void dfs(int u)
    {
        s[++tot] = u;
        vis[u] = 1;
        int v;
        std::priority_queue<int,std::vector<int>,std::greater<int> > q;
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            if(vis[v])
                continue;
            q.push(v);
        }
        while(!q.empty())
        {
            v = q.top();
            q.pop();
            dfs(v);
        }
    }
    void solve()
    {
        ans[1] = 1<<30;
        for(int i = 1;i<=m;++i)
        {
            int a = i * 2 - 1, b = i * 2;
            int v = E[a].to,u = E[b].to;
            E[a].to = E[b].to = 0;
            memset(vis,0,sizeof(vis));
            vis[0] = 1;
            tot = 0;
            dfs(1);
            E[a].to = v, E[b].to = u;
            if(tot != n)
                continue;
            for(int j = 1;j<=n;++j)
                if(s[j] < ans[j])
                {
                    for(int k = 1;k<=n;++k)
                        ans[k] = s[k];
                    break;
                }
                else if(s[j] > ans[j])
                    break;
        }
        for(int i = 1;i<=n;++i)
            printf("%d ",ans[i]);
    }
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=m;++i)
    {
        int u,v;
        read(u);
        read(v);
        add(u,v);
        add(v,u);
    }
    if(m == n - 1)
        D::solve();
    else
        C::solve();
    return 0;
}
