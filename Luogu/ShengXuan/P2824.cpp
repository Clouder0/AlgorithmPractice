#include <cstdio>
#include <set>
using namespace std;
const int maxn = 1e5 + 100;
int n,m,q;
int root[maxn],sum[maxn << 5],L[maxn << 5],R[maxn << 5],ind,st[maxn << 5],top;
int rev[maxn];
inline int newnode(){return top ? st[top--] : ++ind;}
inline void delnode(int x){if(x) L[x] = R[x] = sum[x] = 0,st[++top] = x;}
void insert(int l,int r,int &p,int pos)
{
    if(!p) p = newnode();
    sum[p] = 1;
    if(l == r) return;
    int mid = l + r >> 1;
    if (pos <= mid) insert(l, mid, L[p], pos);
    else insert(mid + 1, r, R[p], pos);
}
int ask(int l,int r,int p)
{
    if(l == r) return l;
    int mid = l + r >> 1;
    return sum[L[p]] ? ask(l,mid,L[p]) : ask(mid + 1,r,R[p]);
}
int merge(int x,int y)
{
    if(!x || !y) return x + y;
    sum[x] += sum[y],L[x] = merge(L[x],L[y]),R[x] = merge(R[x],R[y]),delnode(y);
    return x;
}
void split(int x,int &y,int k,int rev)
{
    if(!x) return;
    y = newnode();
    sum[y] = sum[x] - k, sum[x] = k;
    if(!rev)
    {
        if(k <= sum[L[x]]) split(L[x],L[y],k,rev),std::swap(R[x],R[y]);
        else split(R[x],R[y],k - sum[L[x]],rev);
    }
    else
    {
        if(k <= sum[R[x]]) split(R[x],R[y],k,rev),std::swap(L[x],L[y]);
        else split(L[x],L[y],k - sum[R[x]],rev);
    }
}
set<int> S;
typedef set<int>::iterator IT;
IT cut(int x)
{
    IT it = S.lower_bound(x);
    if(*it == x) return it;
    rev[x] = rev[*--it];
    split(root[*it],root[x],x - *it,rev[*it]);
    return S.insert(x).first;
}
int main()
{
    scanf("%d %d",&n,&m);
    S.insert(n + 1);
    for (int i = 1, x; i <= n; ++i) scanf("%d", &x), insert(0, n, root[i], x), S.insert(i);
    while(m--)
    {
        int opt,l,r;
        scanf("%d %d %d", &opt, &l, &r);
        IT ir = cut(r + 1),il = cut(l);
        ++il;
        for(IT i = il;i != ir;++i) root[l] = merge(root[l],root[*i]);
        rev[l] = opt,S.erase(il,ir);
    } 
    scanf("%d", &q);
    cut(q),cut(q + 1);
    printf("%d\n",ask(0,n,root[q]));
    return 0;
}