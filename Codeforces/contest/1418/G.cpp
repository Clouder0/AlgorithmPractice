#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 5e5 + 100;
int n,a[maxn];
vector<int> pos[maxn];
int minn[maxn << 2], cnt[maxn << 2], tag[maxn << 2];
#define ls p<<1
#define rs p<<1|1
inline void pushup(int p)
{
    minn[p] = min(minn[ls], minn[rs]);
    cnt[p] = 0;
    if (minn[p] == minn[ls]) cnt[p] += cnt[ls];
    if (minn[p] == minn[rs]) cnt[p] += cnt[rs];
}
inline void pushdown(int p)
{
    if (!tag[p]) return;
    minn[ls] += tag[p], minn[rs] += tag[p];
    tag[ls] += tag[p], tag[rs] += tag[p];
    tag[p] = 0;
}
void build(int l,int r,int p)
{
    if (l == r) return (void)(cnt[p] = 1);
    int mid = l + r >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), pushup(p);
}
void add(int l,int r,int p,int ll,int rr,int k)
{
    if (l >= ll && r <= rr) return (void)(minn[p] += k, tag[p] += k);
    int mid = l + r >> 1;
    pushdown(p);
    if (ll <= mid) add(l, mid, ls, ll, rr, k);
    if (rr > mid) add(mid + 1, r, rs, ll, rr, k);
    pushup(p);
}
int ask(int l,int r,int p,int ll,int rr)
{
    if(l >= ll && r <= rr) return !minn[p] ? cnt[p] : 0;
    int mid = l + r >> 1,res = 0;
    pushdown(p);
    if(ll <= mid) res = ask(l,mid,ls,ll,rr);
    if(rr > mid) res += ask(mid + 1,r,rs,ll,rr);
    return res;
}
int main()
{
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) pos[i].push_back(0);
    build(1,n,1);
    long long res = 0;
    pos[a[1]].push_back(1), add(1, n, 1, 1, 1, 1);
    for (int i = 2; i <= n; ++i)
    {
        int s = pos[a[i]].size();
        add(1, n, 1, pos[a[i]][s - 1] + 1, i, 1);
        if (s >= 3) add(1, n, 1, pos[a[i]][s - 3] + 1, pos[a[i]][s - 2], -1);
        if (s >= 4) add(1, n, 1, pos[a[i]][s - 4] + 1, pos[a[i]][s - 3], 1);
        pos[a[i]].push_back(i);
        if (minn[1] == 0) res += cnt[1] - (n - i);
    }
    printf("%lld\n",res);
    return 0;
}