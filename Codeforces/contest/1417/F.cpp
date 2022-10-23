#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
const int maxn = 2e5 + 100, maxm = 3e5 + 100,maxq = 5e5 + 100;
int n,p[maxn],m, q;
struct Edge
{
    int u,v,time;
}EE[maxm];
bool cmp(const Edge &a,const Edge &b){return a.time > b.time;}
int query[maxq], querytime[maxq], qcnt;
int ANS[maxq];
int fa[maxn];
multiset<int> S[maxn];
int find(int x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
void merge(int x,int y)
{
    x = find(x),y = find(y);
    if(x == y) return;
    if(S[x].size() < S[y].size()) swap(x,y);
    for (multiset<int>::iterator it = S[y].begin(); it != S[y].end(); ++it) S[x].insert(*it);
    S[y].clear();
    fa[y] = x;
}
int main()
{
    scanf("%d %d %d", &n,&m,&q);
    for (int i = 1; i <= n; ++i) scanf("%d", p + i);
    for (int i = 1; i <= n; ++i) fa[i] = i,S[i].insert(p[i]);
    for (int i = 1; i <= m; ++i) scanf("%d %d",&EE[i].u,&EE[i].v),EE[i].time = q + 1;
    for (int i = 1; i <= q; ++i)
    {
        int opt,x;
        scanf("%d %d",&opt,&x);
        if(opt == 1) query[++qcnt] = x,querytime[qcnt] = i;
        else EE[x].time = i;
    }
    sort(EE + 1,EE + 1 + m,cmp);
    int p = 1;
    for (int i = qcnt; i; --i)
    {
        while(EE[p].time > querytime[i]) merge(EE[p].u,EE[p].v),++p;
        int x = find(query[i]);
        ANS[i] = *S[x].begin(), S[x].erase(S[x].begin());
    }
    for (int i = 1; i <= qcnt; ++i) printf("%d\n",ANS[i]);
    return 0;
}