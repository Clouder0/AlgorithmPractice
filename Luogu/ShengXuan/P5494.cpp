#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int maxn = 4e5 + 100;
int n,m;
int root[maxn], rcnt = 1, sum[maxn << 5], L[maxn << 5], R[maxn << 5],ind,s[maxn << 5],top;
inline int newnode(){return top ? s[top--] : ++ind;}
inline void delnode(int x){sum[x] = L[x] = R[x] = 0,s[++top] = x;}
void modify(int l,int r,int &p,int pos,int k)
{
    if(!p) p = newnode();
    sum[p] += k;
    if (l == r) return;
    int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, L[p], pos, k);
    else modify(mid + 1, r, R[p], pos, k);
}
int merge(int x,int y)
{
    if(!x || !y) return x + y;
    sum[x] += sum[y], L[x] = merge(L[x], L[y]), R[x] = merge(R[x], R[y]), delnode(y);
    return x;
}
void split(int x,int &y,int k)
{
    if(!x) return;
    y = newnode();
    int val = sum[L[x]];
    if(k > val) split(R[x],R[y],k - val);
    else std::swap(R[x], R[y]);
    if (k < val) split(L[x], L[y], k);
    sum[y] = sum[x] - k, sum[x] = k;
}
int ask(int l,int r,int p,int ll,int rr)
{
    if(ll > rr) return 0;
    if(!p) return 0;
    if(l >= ll && r <= rr) return sum[p];
    int mid = l + r >> 1,ans = 0;
    if(ll <= mid)ans = ask(l,mid,L[p],ll,rr);
    if(rr > mid) ans += ask(mid + 1,r,R[p],ll,rr);
    return ans;
}
int askkth(int l,int r,int p,int k)
{
    if(l == r) return l;
    int mid = l + r >> 1;
    if (k <= sum[L[p]]) return askkth(l, mid, L[p], k);
    else return askkth(mid + 1, r, R[p], k - sum[L[p]]);
}
signed main()
{
    scanf("%lld %lld",&n,&m);
    for (int i = 1, x; i <= n; ++i) 
        scanf("%lld", &x), modify(1, n, root[1], i, x);
    while (m--)
    {
        int opt,p,x,y,t,q,k;
        scanf("%lld",&opt);
        if(opt == 0) 
        {
            scanf("%lld %lld %lld", &p, &x, &y);
            int num1 = ask(1, n, root[p], 1, y), num2 = ask(1, n, root[p], x, y),tmproot = 0;
            split(root[p], root[++rcnt], num1 - num2), split(root[rcnt], tmproot, num2);
            root[p] = merge(root[p], tmproot);
        }
        else if(opt == 1)
        {
            scanf("%lld %lld",&p,&t);
            root[p] = merge(root[p],root[t]);
        }
        else if(opt == 2)
        {
            scanf("%lld %lld %lld",&p,&x,&q);
            modify(1,n,root[p],q,x);
        }
        else if(opt == 3)
        {
            scanf("%lld %lld %lld",&p,&x,&y);
            printf("%lld\n",ask(1,n,root[p],x,y));
        }
        else
        {
            scanf("%lld %lld",&p,&k);
            if(sum[root[p]] >= k) printf("%lld\n",askkth(1,n,root[p],k));
            else puts("-1");
        }
    }
    return 0;
}