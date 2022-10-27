#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 2e6 + 100;
vector<int> V[maxn];
int n,m;
int dfn[maxn],low[maxn],cnt;
int ins[maxn],st[maxn],top;
int bel[maxn],sccnum;
void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    st[++top] = u,ins[u] = 1;
    for(vector<int>::iterator it = V[u].begin();it!=V[u].end();++it)
    {
        int v = *it;
        if(!dfn[v]) tarjan(v),low[u] = std::min(low[u],low[v]);
        else if(ins[v]) low[u] = std::min(low[u],dfn[v]);
    }
    if(low[u] == dfn[u])
    {
        ++sccnum;
        while (st[top] != u) bel[st[top]] = sccnum, ins[st[top--]] = false;
        --top,bel[u] = sccnum,ins[u] = false;
    }
}
int main()
{
    scanf("%d %d",&n,&m);
    //[1,n] for true,[n+1,2n] for false
    for (int i = 1; i <= m; ++i) 
    {
        int a,av,b,bv;
        scanf("%d %d %d %d",&a,&av,&b,&bv);
        if (av && bv) 
            printf("add %d %d\n",b+n,a),printf("add %d %d\n",a+n,b),V[a + n].push_back(b), V[b + n].push_back(a);  //a true or b true
        else if (av) 
            printf("add %d %d\n",a+n,b+n),printf("add %d %d\n",b,a),V[a + n].push_back(b + n), V[b].push_back(a);           //a true or b false
        else if (bv) 
            printf("add %d %d\n",b+n,a+n),printf("add %d %d\n",a,b),V[b + n].push_back(a + n), V[a].push_back(b);  //a false or b true
        else 
            printf("add %d %d\n",a,b+n),printf("add %d %d\n",b,a+n),V[a].push_back(b + n), V[b].push_back(a + n);  //a false or b false
    }
    for (int i = 1; i <= n * 2; ++i) if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; ++i) if (bel[i] == bel[i + n]) { puts("IMPOSSIBLE"); return 0; }
    puts("POSSIBLE");
    for(int i = 1;i<=n;++i) if(bel[i] < bel[i+n]) printf("1 "); else printf("0 ");
    return 0;
}
