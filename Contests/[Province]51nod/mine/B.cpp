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
#include <queue>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
struct node
{
    int to,next;
    node(){}
    node(const int &_to,const int &_next) : to(_to),next(_next){}
}lines[20000000];
int head[3010];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    lines[++tot] = node(y,head[x]),head[x] = tot;
}
int n;
char s[3100];
queue<int> q;
bool vis[3100];
int dis[3100][3100];
int maxd;
void bfs(int s)
{
    int *d = dis[s];
    memset(vis,0,sizeof(vis));
    q.push(s);
    d[s] = 1;
    int u,v;
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        if(vis[u])
            continue;
        vis[u] = true;
        if(d[u] > maxd)
            maxd = d[u];
        for(int p = head[u];p;p=lines[p].next)
        {
            v = lines[p].to;
            if(vis[v])
                continue;
            if(d[v] > d[u] + 1 || d[v] == 0)
            {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
}
int ans;
int main()
{
    read(n);
    scanf("%s",s+1);
    for(int i = 1;i<n;++i)
        add(i,i+1),add(i+1,i);
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=n;++j)
            if(s[i] == s[j])
                add(i,j),add(j,i);
    for(int i = 1;i<=n;++i)
        bfs(i);
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=n;++j)
            if(dis[i][j] == maxd)
                ++ans;
    ans >>= 1;
    printf("%d %d",maxd - 1,ans);
    return 0;
}