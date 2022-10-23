#include <cstdio>
#include <algorithm>
#include <cmath>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 3e4 + 100;
const int maxm = 2e5 + 100;
int n,q;
struct  node
{
    int l,r,id,pos;
}Q[maxm];
bool cmp(const node &a,const node &b)
{
    if(a.pos != b.pos) return a.pos < b.pos;
    if(a.pos & 1) return a.r < b.r;
    else return a.r > b.r;
}
int a[maxn],cnt[1000010],ANS[maxm];
int main()
{
    read(n);
    for(int i = 1;i<=n;++i) read(a[i]);
    read(q);
    int size = n / std::sqrt(n);
    for(int i = 1;i<=q;++i) read(Q[i].l),read(Q[i].r),Q[i].id = i,Q[i].pos = Q[i].l / size;
    std::sort(Q + 1,Q + 1 + q,cmp);
    int l = 1,r = 0,ans = 0;
    for(int i = 1;i<=q;++i)
    {
        while(l > Q[i].l) ans += !cnt[a[--l]]++;
        while(r < Q[i].r) ans += !cnt[a[++r]]++;
        while(l < Q[i].l) ans -= !--cnt[a[l++]];
        while(r > Q[i].r) ans -= !--cnt[a[r--]];
        ANS[Q[i].id] = ans;
    }
    for(int i = 1;i<=q;++i) printf("%d\n",ANS[i]);
    return 0;
}