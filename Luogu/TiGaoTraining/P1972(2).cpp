#include <cstdio>
#include <cmath>
#include <algorithm>
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
const int maxn = 1e6 + 100;
int n,m;
int a[maxn];
struct  query
{
    int l,r,id,pos;
}Q[maxn];
bool cmp(const query &a,const query &b)
{
    if(a.pos != b.pos) return a.pos < b.pos;
    if(a.pos & 1) return a.r < b.r;
    else return a.r > b.r;
}
int cnt[maxn],ANS[maxn];
int main()
{
    read(n);
    for(int i = 1;i<=n;++i) read(a[i]);
    read(m);
    int size = n / std::sqrt(m);
    for(int i = 1;i<=m;++i) read(Q[i].l),read(Q[i].r),Q[i].id = i,Q[i].pos = Q[i].l / size;
    std::sort(Q + 1,Q + 1 + m,cmp);
    int l = 1,r = 0,ans = 0;
    for(int i = 1;i<=m;++i)
    {
        while(l > Q[i].l) --l,ans += !cnt[a[l]],cnt[a[l]]++;
        while(r < Q[i].r) ++r,ans += !cnt[a[r]],cnt[a[r]]++;
        while(l < Q[i].l) --cnt[a[l]],ans -= !cnt[a[l]],++l;
        while(r > Q[i].r) --cnt[a[r]],ans -= !cnt[a[r]],--r;
        ANS[Q[i].id] = ans;
    }
    for(int i = 1;i<=m;++i) printf("%d\n",ANS[i]);
    return 0;
}