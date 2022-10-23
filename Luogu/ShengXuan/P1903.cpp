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
const int maxn = 133333 + 100;
int n,m;
int cnt[1000010];
int a[maxn];
struct node
{
    int l,r,t,id;
}Q[maxn],C[maxn];
int qtot,ctot,size;
int ANS[maxn];
int l = 1,r = 0,t = 0,ans = 0;
bool cmp(const node &a,const node &b)
{
    if(a.l / size != b.l / size)  return a.l < b.l;
    if(a.r / size != b.r / size) return a.r < b.r;
    return a.t < b.t;
}
void update(int l,int r,int t)
{
    int pos = C[t].l,&col = C[t].r;
    if(pos >= l && pos <= r)
    {
        ans -= !--cnt[a[pos]];
        ans += !cnt[col]++;
    }
    std::swap(a[pos],col);
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(a[i]);
    size = std::pow(n,0.7); 
    for(int i = 1;i<=m;++i)
    {
        char s[5];
        scanf("%s",s + 1);
        if(s[1] == 'Q')
        {
            read(Q[++qtot].l),read(Q[qtot].r);
            Q[qtot].id = qtot,Q[qtot].t = ctot;
        }
        else
        {
            read(C[++ctot].l),read(C[ctot].r);
            C[ctot].id = ctot;
        }
    }
    std::sort(Q + 1,Q + 1 + qtot,cmp);
    for(int i = 1;i<=qtot;++i)
    {
        while(l > Q[i].l) --l,ans += !cnt[a[l]],cnt[a[l]]++;
        while(r < Q[i].r) ++r,ans += !cnt[a[r]],cnt[a[r]]++;
        while(l < Q[i].l) --cnt[a[l]],ans -= !cnt[a[l]],++l;
        while(r > Q[i].r) --cnt[a[r]],ans -= !cnt[a[r]],--r;
        while(t < Q[i].t) update(Q[i].l,Q[i].r,++t);
        while(t > Q[i].t) update(Q[i].l,Q[i].r,t--);
        ANS[Q[i].id] = ans;
    }
    for(int i = 1;i<=qtot;++i) printf("%d\n",ANS[i]);
    return 0;
}