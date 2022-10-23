#include <cstdio>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <map>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 100;
const int maxx = 4e4 + 500;
int n,m,tot,a[maxn],len[maxn],cnt[maxn];
map<int,int> mp;
bitset<maxn> ans[maxx],now;
struct node
{
    int l,r,id,pos;
    bool operator<(const node &b) const 
    {
        if(pos != b.pos) return pos < b.pos;
        if(pos & 1) return r < b.r;
        return r > b.r;
    }
}Q[maxn];
inline void add(int x)
{
//    if(a[x] - cnt[a[x]] > maxn || a[x] - cnt[a[x]] < 0) exit(0);
    now[a[x] - cnt[a[x]]++] = 1;
}
inline void del(int x)
{
//    if(a[x] - cnt[a[x]] + 1 > maxn || a[x] - cnt[a[x]] + 1 < 0) exit(0);
    now[a[x] - (--cnt[a[x]])] = 0;
}
void solve(int x)
{
    if(x <= 0) return;
    tot = 0;
    for(int i = 1;i<=n;++i) cnt[a[i]] = 0,len[i] = 0;
    int size = n / sqrt(x);
    for(int i = 1;i<=x;++i)
    {
        Q[++tot].id = i,read(Q[tot].l),read(Q[tot].r),Q[tot].pos = Q[tot].l / size,len[i] += Q[tot].r - Q[tot].l + 1;
        Q[++tot].id = i,read(Q[tot].l),read(Q[tot].r),Q[tot].pos = Q[tot].l / size,len[i] += Q[tot].r - Q[tot].l + 1;
        Q[++tot].id = i,read(Q[tot].l),read(Q[tot].r),Q[tot].pos = Q[tot].l / size,len[i] += Q[tot].r - Q[tot].l + 1;
    }
    for(int i = 1;i<=x;++i) ans[i].set();
    sort(Q + 1,Q + 1 + tot);
    int l = 1,r = 0;
    now.reset();
    for(int i = 1;i<=tot;++i)
    {
        while(l > Q[i].l) add(--l);
        while(r < Q[i].r) add(++r);
        while(l < Q[i].l) del(l++);
        while(r > Q[i].r) del(r--);
        ans[Q[i].id] &= now;
    }
    for(int i = 1;i<=x;++i) printf("%d\n",len[i] - ans[i].count() * 3);
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(a[i]),mp[a[i]]++;
    for(map<int,int>::iterator it = mp.begin(),it2 = ++mp.begin();it2!=mp.end();++it,++it2) it2->second += it->second;
    for(int i = 1;i<=n;++i) a[i] = mp[a[i]];
    solve(m / 3),solve(m / 3),solve(m - 2 * (m / 3));
    return 0;
}