#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <set>
using namespace std;
const int maxn = 2e5 + 100;
struct node
{
    int to,next;
}E[maxn];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
map<string,int> names;
int namecnt;
int n,m;
struct Qe
{
    int next,id,dep;
}Q[maxn];
int Qh[maxn],ANS[maxn];
inline void addQ(const int &x,const int &id,const int &dep)
{
    static int tot = 0;
    Q[++tot].next = Qh[x],Qh[x] = tot,Q[tot].id = id,Q[tot].dep = dep;
}
int treeroot[maxn],treecnt;
int val[maxn];
int root[maxn],L[maxn * 4],R[maxn * 4],st[maxn * 4],top,ind;
set<int> S[maxn *4];
inline int newnode(){return top ? st[top--] : ++ind;}
inline void delnode(int x){S[x].clear(),L[x] = R[x] = 0,st[++top] = x;}
void insert(int l,int r,int &p,int pos,int k)
{
    if(!p) p = newnode();
    if(l == r) return (void)(S[p].insert(k));
    int mid = l + r >> 1;
    if(pos <= mid) insert(l,mid,L[p],pos,k);
    else insert(mid + 1,r,R[p],pos,k);
}
int ask(int l,int r,int p,int pos)
{
    if(!p) return 0;
    if(l == r) return S[p].size();
    int mid = l + r >> 1;
    if(pos <= mid) return ask(l,mid,L[p],pos);
    else return ask(mid + 1,r,R[p],pos);
}
int merge(int l,int r,int x,int y)
{
    if(!x || !y) return x + y;
    if(l == r) 
    {
        for(set<int>::iterator it = S[y].begin();it!=S[y].end();++it) S[x].insert(*it);
        delnode(y);
        return x;
    }
    int mid = l + r >> 1;
    L[x] = merge(l,mid,L[x],L[y]),R[x] = merge(mid + 1,r,R[x],R[y]),delnode(y);
    return x;
}
int dep[maxn];
void dfs(int u)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        dep[v] = dep[u] + 1,dfs(v),root[u] = merge(1,200000,root[u],root[v]);
    }
    insert(1,200000,root[u],dep[u],val[u]);
    for (int p = Qh[u]; p; p = Q[p].next) ANS[Q[p].id] = ask(1, 200000, root[u], dep[u] + Q[p].dep);
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);
    cin >> n;
    for (int i = 1,x; i <= n; ++i) 
    {
        string nam;
        cin >> nam >> x;
        map<string,int>::iterator it = names.find(nam);
        if (it == names.end()) {names[nam] = ++namecnt;val[i] = namecnt;}
        else val[i] = it->second;
        if (!x) { treeroot[++treecnt] = i; continue; }
        add(x,i);
    }
    cin >> m;
    for (int i = 1, a, b; i <= m; ++i) cin >> a >> b, addQ(a, i, b);
    for (int i = 1; i <= treecnt; ++i) dep[treeroot[i]] = 1, dfs(treeroot[i]);
    for (int i = 1; i <= m; ++i) printf("%d\n", ANS[i]);
    return 0;
}