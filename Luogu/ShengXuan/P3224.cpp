#include <cstdio>
const int maxn = 5e5 + 100;
int n, m, q, id[maxn];
int fa[maxn],root[maxn];
int find(int x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
int sum[maxn << 5],L[maxn << 5],R[maxn << 5],s[maxn << 5],top,ind;
inline int newnode() {return top ? s[top--] : ++ind;}
inline void delnode(int x){sum[x] = L[x] = R[x] = 0,s[++top] = x;}
int merge(int x,int y)
{
    if(!x || !y) return x + y;
    sum[x] += sum[y],L[x] = merge(L[x],L[y]),R[x] = merge(R[x],R[y]),delnode(y);
    return x;
}
void modify(int l,int r,int &p,int pos,int k)
{
    if(!p) p = newnode();
    sum[p]  += k;
    if(l == r) return;
    int mid = l + r >> 1;
    if(pos <= mid) modify(l,mid,L[p],pos,k);
    else modify(mid + 1,r,R[p],pos,k);
}
int askkth(int l,int r,int p,int k)
{
    if(l == r) return l;
    int mid = l + r >> 1;
    if(k <= sum[L[p]]) return askkth(l,mid,L[p],k);
    else return askkth(mid + 1, r, R[p],  k - sum[L[p]]);
}
void unite(int x,int y)
{
    x = find(x),y = find(y);
    if(x == y) return;
    root[x] = merge(root[x], root[y]), fa[y] = x;
}
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1, x; i <= n; ++i) scanf("%d", &x), modify(1, n, root[i], x, 1), id[x] = i;
    for (int i = 1, u, v; i <= m; ++i) scanf("%d %d", &u, &v), unite(u, v);
    scanf("%d",&q);
    while(q--)
    {
        char S[3];
        int x,y;
        scanf("%s %d %d",s + 1,&x,&y);
        if(s[1] == 'Q') 
        {
            int rt = find(x);
            if(sum[root[rt]] < y) puts("-1");
            else printf("%d\n",id[askkth(1,n,root[rt],y)]);
        }
        else unite(x,y);
    }
    return 0;
}