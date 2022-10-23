#include <cstdio>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e5 + 100;
const int mod = 10007;
struct node
{
    int to,next;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int n;
int w[maxn];
int sum,ans;
void dfs(int u,int fa,int tfa)
{
    sum += w[u] * w[tfa];
    if(sum > mod) sum %= mod;
    ans = max(ans,w[u] * w[tfa]);
    int t = 0,tmax = 0;
    for(int p = head[u];p;p=E[p].next)
    {   
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v,u,fa);
        sum += w[v] * t;
        if(sum > mod) sum %= mod;
        t += w[v];
        if(t > mod) t %= mod;
        ans = max(ans,w[v] * tmax);
        if(w[v] > tmax) tmax = w[v];
    }
}
int main()
{
    read(n);
    for(int i = 1;i<n;++i)
    {
        int a,b;
        read(a),read(b);
        add(a,b),add(b,a);
    }
    for(int i = 1;i<=n;++i)
        read(w[i]);
    dfs(1,0,0);
    printf("%d %d",ans,(sum<<1) % mod);
    return 0;
}