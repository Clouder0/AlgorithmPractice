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
const int maxn = 1e5 + 100;
int n,m,k;
struct node
{
    int l,r,id,pos;
}Q[maxn];
bool cmp(const node &a,const node &b)
{
    if(a.pos != b.pos) return a.pos < b.pos;
    if(a.pos & 1) return a.r < b.r;
    else return a.r > b.r;
}
int a[maxn],cnt[maxn<<3],ANS[maxn];
int l = 1,r = 0,ans = 0;
inline void add(int x){ans += cnt[a[x]^k],++cnt[a[x]];}
inline void del(int x){--cnt[a[x]],ans -= cnt[a[x]^k];}
int main()
{
    read(n),read(m),read(k);
    for(int i = 1;i<=n;++i) read(a[i]),a[i] ^= a[i-1];
    int size = std::sqrt(n);
    for(int i = 1;i<=m;++i) Q[i].id = i,read(Q[i].l),read(Q[i].r),Q[i].pos = Q[i].l / size;
    std::sort(Q + 1,Q + 1 + m,cmp);
    cnt[0] = 1;
    for(int i = 1;i<=m;++i)
    {
        while(l > Q[i].l) --l,add(l-1);
        while(r < Q[i].r) add(++r);
        while(l < Q[i].l) del(l-1),++l;
        while(r > Q[i].r) del(r--);
        ANS[Q[i].id] = ans;
    }
    for(int i = 1;i<=m;++i) printf("%d\n",ANS[i]);
    return 0;
}