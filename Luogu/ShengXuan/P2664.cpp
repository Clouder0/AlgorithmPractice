#include <cstdio>
#define int long long
#define WALK for(int p = head[u];p;p=E[p].next)
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 100;
struct node
{
    int to,next;
}E[maxn<<1];
int head[maxn],tot;
inline void add(const int &x,const int &y){E[++tot].next = head[x],E[tot].to = y,head[x] = tot;}
int n;
int color[maxn];
int size[maxn],maxp[maxn],root,treeSize;
int vis[maxn];
void getroot(int u,int fa)
{
    size[u] = 1,maxp[u] = 0;
    WALK
    {
        int v = E[p].to;
        if(v == fa || vis[v]) continue;
        getroot(v,u);
        size[u] += size[v];
        maxp[u] = max(maxp[u],size[v]);
    }
    maxp[u] = max(maxp[u],treeSize - size[u]);
    if(maxp[u] < maxp[root]) root = u;
}
int cnt[maxn],colorSum[maxn],sum;
int ans[maxn],otherSize;
void dfs1(int u,int fa)
{
    size[u] = 1,cnt[color[u]]++;
    WALK
    {
        int v = E[p].to;
        if(v == fa || vis[v]) continue;
        dfs1(v,u);
        size[u] += size[v];
    }
    if(cnt[color[u]] == 1)
    {
        //首次出现
        sum += size[u];
        colorSum[color[u]] += size[u];
    }
    cnt[color[u]]--;
}
void modify(int u,int fa,int k)
{
    //不更新size的dfs1
    cnt[color[u]]++;
    WALK
    {
        int v = E[p].to;
        if(v == fa || vis[v]) continue;
        modify(v,u,k);
    }
    if(cnt[color[u]] == 1)
    {
        sum += size[u] * k;
        colorSum[color[u]] += size[u] * k;
    }
    cnt[color[u]]--;
}
int colorNum;
void dfs2(int u,int fa)
{
    cnt[color[u]]++;
    if(cnt[color[u]] == 1)
    {
        //从上到下首次进入
        sum -= colorSum[color[u]];//经过该点后，与该点同色的点不再计算贡献
        ++colorNum;
    }
    ans[u] += sum + colorNum * otherSize;
    WALK
    {
        int v = E[p].to;
        if(vis[v] || v == fa) continue;
        dfs2(v,u);
    }
    if(cnt[color[u]] == 1)
    {
        sum += colorSum[color[u]];
        --colorNum;
    }
    --cnt[color[u]];
}
void clear(int u,int fa)
{
    cnt[color[u]] = colorSum[color[u]] = 0;
    WALK
    {
        int v = E[p].to;
        if(vis[v] || v == fa) continue;
        clear(v,u);
    }
}
void calc(int u)
{
    dfs1(u,0);
    ans[u] += sum;
    WALK
    {
        int v = E[p].to;
        if(vis[v]) continue;

        cnt[color[u]]++;//模拟modify从u开始
        sum -= size[v];
        colorSum[color[u]] -= size[v];
        modify(v,u,-1);//该子树中贡献被移除
        cnt[color[u]]--;

        otherSize = size[u] - size[v];
        dfs2(v,u);

        cnt[color[u]]++;//回溯
        sum += size[v];
        colorSum[color[u]] += size[v];
        modify(v,u,1);
        cnt[color[u]]--;
    }
    sum = colorNum = 0;
    clear(u,0);
}
void solve(int u)
{
    vis[u] = 1;
    calc(u);
    WALK
    {
        int v = E[p].to;
        if(vis[v]) continue;
        treeSize = size[v],maxp[root = 0] = 1<<30,getroot(v,u);
        solve(root);
    }
}
signed main()
{
    read(n);
    for(int i = 1;i<=n;++i) read(color[i]);
    for(int i = 1;i<n;++i)
    {
        int a,b;
        read(a),read(b);
        add(a,b),add(b,a);
    }
    maxp[root = 1] = n,treeSize = n,getroot(1,0);
    solve(root);
    for(int i = 1;i<=n;++i) printf("%lld\n",ans[i]);
    return 0;
}