#include <cstdio>
#include <algorithm>
#include <vector>
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 1e5 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int &x, const int &y)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].next = head[x];
    head[x] = tot;
}
std::vector<int> V[maxn];
int n, m;
namespace Dec
{
    int fa[maxn],size[maxn],son[maxn],dep[maxn];
    void dfs1(int u)
    {
        size[u] = 1;
        int v;
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            if(v == son[u])
                continue;
            fa[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            size[u] += size[v];
            if(size[son[u]] < size[v])
                son[u] = v;
        }
    }
    int dfn[maxn],time,top[maxn];
    void dfs2(int u,int topf)
    {
        dfn[u] = ++time;
        top[u] = topf;
        if(!son[u])
            return;
        dfs2(son[u],topf);
        int v;
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            if(v == fa[u] || v == son[u])
                continue;
            dfs2(v,v);
        }
    }
    inline int lca(int x,int y)
    {
        while(top[x] != top[y])
        {
            if(dep[top[x]] > dep[top[y]])
            {
                int t = x;
                x = y;
                y = t;
            }
            x = fa[top[x]];
        }
        return dep[x] < dep[y] ? x : y;
    }
}
const bool cmp(const int &x,const int &y)
{
    return Dec::dep[x] < Dec::dep[y];
}
int is[maxn];
bool iis[maxn];
int s[maxn],top;
long long dp[maxn];
int size[maxn];
void ddfs(int x,int f)
{
	dp[x] = size[x] = 0;
	for(int i = 0;i < V[x].size();i++)
	{
		int v = V[x][i];
		if(v == f) continue;
		ddfs(v,x);
		dp[x] += dp[v],size[x] += size[v]; 
	}
	if(iis[x]) dp[x] += size[x],size[x] = 1;
	else if(size[x] > 1) dp[x]++,size[x] = 0;
}
inline void addE(int x,int y)
{
    V[x].push_back(y),V[y].push_back(x);
}
void BuildTree(int k)
{
    for (int p = 1; p <= k; ++p)
        read(is[p]),iis[is[p]] = 1;
    std::sort(is + 1, is + 1 + k, cmp);
    s[top = 1] = 1;
    V[1].clear();
    for (int i = 1, l; i <= k; i += 1)
        if (is[i] != 1) //如果1号节点是关键节点就不要重复添加
        {
            l = Dec::lca(is[i], s[top]); //计算当前节点与栈顶节点的LCA
            if (l != s[top])
            {
                while (Dec::dfn[l] < Dec::dfn[s[top - 1]])
                    addE(s[top-1],s[top]),top--;
                if (Dec::dfn[l] > Dec::dfn[s[top - 1]])
                    V[l].clear(),addE(l,s[top]),s[top] = l;
                else
                    addE(l,s[top--]);
            }
            V[is[i]].clear(),s[++top] = is[i];
        }
    for (int i = 1; i < top; i += 1)
        addE(s[i],s[i+1]);
}
int main()
{
    read(n);
    for(int i = 1;i<n;++i)
    {
        int a,b;
        read(a);
        read(b);
        add(a,b);
        add(b,a);
    }
    Dec::dep[1] = 1;
    Dec::dfs1(1);
    Dec::dfs2(1,1);
    read(m);
    for(int i = 1;i<=m;++i)
    {
        int k;
        read(k);
        BuildTree(k);
        ddfs(1,0);
        printf("%d\n",dp[1]);
        for(int i = 1;i<=k;++i)
            iis[is[i]] = 0;
    }
    return 0;
}