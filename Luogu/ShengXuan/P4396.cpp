#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 100;
int n,m;
int a[maxn];
struct node
{
    int l,r,pos,id,a,b;
    bool operator<(const node &b) const
    {
        if(pos != b.pos) return pos < b.pos;
        if(pos & 1) return r < b.r;
        return r > b.r;
    }
}Q[maxn];
std::pair<int,int> ANS[maxn];
int cnt[maxn],times[maxn],sum[maxn],L[maxn],R[maxn],pos[maxn],maxx;
inline void build()
{
    int size = sqrt(maxx);
    int num = maxx / size;
    for(int i = 1;i<=num;++i)
    {
        L[i] = R[i-1] + 1;
        R[i] = L[i] + size - 1;
        for(int j = L[i];j<=R[i];++j) pos[j] = i;
    }
    if(R[num] < n)
    {
        L[num + 1] = R[num] + 1;
        R[++num] = n;
        for(int j = L[num];j<=n;++j) pos[j] = num;
    }
}
inline void modify(int x,int k)
{
    if(k == 0) return;
    int p = pos[x];
    sum[p] += k,times[x] += k;
    if(times[x] == k) cnt[p]++;
    else if(times[x] == 0) cnt[p]--;
}
int tcnt[maxn];
inline std::pair<int,int> ask(int ll,int rr)
{
    int lp = pos[ll],rp = pos[rr];
    std::pair<int,int> ans;
    if(lp == rp)
    {
        for(int i = ll;i<=rr;++i) ans.first += times[i],ans.second += times[i] > 0;
        return ans;
    }
    for(int i = lp + 1;i < rp;++i) ans.first += sum[i],ans.second += cnt[i];
    for(int i = ll;i<=R[lp];++i) ans.first += times[i],ans.second += times[i] > 0;
    for(int i = L[rp];i<=rr;++i) ans.first += times[i],ans.second += times[i] > 0;
    return ans;
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(a[i]),maxx = std::max(maxx,a[i]);
    build();
    int size = sqrt(n);
    for(int i = 1;i<=m;++i) read(Q[i].l),read(Q[i].r),read(Q[i].a),read(Q[i].b),Q[i].pos = Q[i].l / size,Q[i].id = i;
    std::sort(Q + 1,Q + 1 + m);
    int l = 1,r = 0;
    for(int i = 1;i<=m;++i)
    {
        while(l > Q[i].l) modify(a[--l],1);
        while(r < Q[i].r) modify(a[++r],1);
        while(l < Q[i].l) modify(a[l++],-1);
        while(r > Q[i].r) modify(a[r--],-1);
        ANS[Q[i].id] = ask(Q[i].a,Q[i].b);
    }
    for(int i = 1;i<=m;++i) printf("%d %d\n",ANS[i].first,ANS[i].second);
    return 0;
}