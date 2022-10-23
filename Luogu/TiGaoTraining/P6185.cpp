#include <cstdio>
#include <cstring>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 10;
int T;
int n,m;
int a[maxn];
struct node
{
    int to,next;
}E[maxn<<1],F[maxn<<1];
int headE[maxn],headF[maxn],totE,totF;
inline void addE(const int &x,const int &y){E[++totE].to = y;E[totE].next = headE[x];headE[x] = totE;}
inline void addF(const int &x,const int &y){F[++totF].to = y;F[totF].next = headF[x];headF[x] = totF;}
int belong[maxn],colorNum;
long long sum[maxn];
int X[maxn],Y[maxn],cnt;
int tag[maxn];
void dfs1(int u,int c)
{
    belong[u] = c;
    sum[c] += a[u];
    int v;
    for(int p = headE[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(!belong[v])
            dfs1(v,c);
    }
}
int color[maxn];
int dfs2(int u,int c,bool &hastag,long long &sb,long long &sw)
{
    color[u] = c;
    hastag |= tag[u];
    if(c)
        sb += sum[u];
    else
        sw += sum[u];
    int res = 1,v;
    for(int p = headF[u];p;p=F[p].next)
    {
        v = F[p].to;
        if(color[v] != -1)
            continue;
        dfs2(v,c^1,hastag,sb,sw);
    }
    return res;
}
int main()
{
    read(T);
    while(T--)
    {
        totE = totF = cnt = colorNum = 0;
        memset(headE,0,sizeof(headE));
        memset(headF,0,sizeof(headF));
        memset(belong,0,sizeof(belong));
        memset(tag,0,sizeof(tag));
        memset(sum,0,sizeof(sum));
        colorNum = 0;
        read(n);
        read(m);
        for(int i = 1;i<=n;++i)
            read(a[i]);
        int t;
        for(int i = 1;i<=n;++i)
            read(t),a[i] = t - a[i];
        int u,v;
        for(int i = 1;i<=m;++i)
        {
            read(t);
            read(u);
            read(v);
            if(t == 2)
                addE(u,v),addE(v,u);
            else
                X[++cnt] = u,Y[cnt] = v;
        }
        for(int i = 1;i<=n;++i)
            if(!belong[i])
                dfs1(i,++colorNum);
        for(int i = 1;i<=cnt;++i)
        {
            if(belong[X[i]] == belong[Y[i]])
                tag[belong[X[i]]] = 1;
            else
            {
                addF(belong[X[i]],belong[Y[i]]);
                addF(belong[Y[i]],belong[X[i]]);
            }
        }
        memset(belong,0,sizeof(belong));
        memset(color,-1,sizeof(color));
        int ans = 1;
        for(int i = 1;i<=colorNum;++i)
            if(color[i] == -1)
            {
                bool hastag = false;
                long long sumb = 0,sumw = 0;
                if(dfs2(i,0,hastag,sumb,sumw))
                {
                    if(hastag)
                        ans &= (((sumb + sumw) %2) == 0);
                    else
                        ans &= (sumb == sumw);
                }
                else
                    ans &= (((sumb + sumw) % 2) == 0);
            }
        if(ans)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}