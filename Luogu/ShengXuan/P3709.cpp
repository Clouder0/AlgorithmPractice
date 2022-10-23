#include <cstdio>
#include <cmath>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e5 + 100;
int n,m;
int a[maxn],H[maxn],tot;
struct node
{
    int l,r,pos,id;
    bool operator<(const node &b) const
    {
        if(pos != b.pos) return pos < b.pos;
        if(pos & 1) return r < b.r;
        return r > b.r;
    }
}Q[maxn];
int times[maxn],cnt[maxn],ans;
int ANS[maxn];
inline void add(int x)
{
    times[cnt[a[x]]]--,times[++cnt[a[x]]]++;
    ans = std::max(cnt[a[x]],ans);
}
inline void del(int x)
{
    times[cnt[a[x]]--]--,times[cnt[a[x]]]++;
    if(!times[ans]) --ans;
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(a[i]),H[++tot] = a[i];
    std::sort(H + 1,H + 1 + tot),tot = std::unique(H + 1,H + 1 + tot) - H - 1;
    for(int i = 1;i<=n;++i) a[i] = std::lower_bound(H + 1,H + 1 + tot,a[i]) - H;
    int size = n / sqrt(m);
    for (int i = 1; i <= m; ++i) read(Q[i].l), read(Q[i].r), Q[i].pos = Q[i].l / size, Q[i].id = i;
    std::sort(Q + 1,Q + 1 + m);
    int l = 1,r = 0;
    for(int i = 1;i<=m;++i)
    {
        while(l > Q[i].l) add(--l);
        while(r < Q[i].r) add(++r);
        while(l < Q[i].l) del(l++);
        while(r > Q[i].r) del(r--);
        ANS[Q[i].id] = ans;
    }
    for(int i = 1;i<=m;++i) printf("%d\n",-ANS[i]);
    return 0;
}