#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
template<typename T>
inline T _min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
inline T _max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxm = 5e4 + 100;
const int maxn = 5e3 + 100;
struct node
{
    int to,next;
}E[maxm<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x];
    E[tot].to = y;
    head[x] = tot;
}
int n,m;
int dfn[maxn],low[maxn],idx;
int st[maxn],ins[maxn],stop;
int belong[maxn];
struct sc
{
    vector<int> V;
    int size;
}scc[maxn];
int num;
void tarjan(int u)
{
    dfn[u] = low[u] = ++idx;
    st[++stop] = u,ins[u] = 1;
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(!dfn[v])
            tarjan(v),low[u] = _min(low[u],low[v]);
        else if(ins[v])
            low[u] = _min(low[u],dfn[v]);
    }
    if(low[u] == dfn[u])
    {
        int p;
        ++num;
        while((p = st[stop--]) != u)
        {
            scc[num].V.push_back(p);
            scc[num].size++;
            ins[p] = false;
        }
        scc[num].V.push_back(u);
        scc[num].size++;
        sort(scc[num].V.begin(),scc[num].V.end());
        ins[u] = false;
    }
}
bool cmp(const sc &a,const sc &b)
{
    if(a.size == b.size)
    {
        for(int i = 1;i<=a.size;++i)
            if(a.V[i] != b.V[i])
                return a.V[i] < b.V[i];
    }
    return a.size > b.size;
}
int main()
{
    read(n);
    read(m);
    int t,x,y;
    while(m--)
    {
        read(x);
        read(y);
        read(t);
        if(t == 1)
            add(x,y);
        else
            add(x,y),add(y,x);
    }
    for(int i = 1;i<=n;++i)
        if(!dfn[i])
            tarjan(i);
    sort(scc+1,scc+1+num,cmp);
    printf("%d\n",scc[1].size);
    for(vector<int>::iterator it = scc[1].V.begin();it!=scc[1].V.end();++it)
        printf("%d ",*it);
    return 0;
}