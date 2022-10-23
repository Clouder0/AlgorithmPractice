#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e6 + 100;
struct query
{
    int l,r,id;
    bool operator<(const query &b){return r < b.r;}
}Q[maxn];
int n,m;
int a[maxn],last[maxn];
int sum[maxn],ans[maxn];
inline void add(int x,int k)
{
    for(;x<=n;x+=x&-x) sum[x] += k;
}
inline int ask(int x)
{
    int res = 0;
    for(;x;x-=x&-x) res += sum[x];
    return res;
}
int main()
{
    read(n);
    for(int i = 1;i<=n;++i) read(a[i]);
    read(m);
    for(int i = 1;i<=m;++i) read(Q[i].l),read(Q[i].r),Q[i].id = i;
    std::sort(Q + 1,Q + 1 + m);
    int p = 1;
    for(int i = 1;i<=m;++i)
    {
        while(p <= Q[i].r)
        {
            if(last[a[p]] != 0) add(last[a[p]],-1);
            add(p,1);
            last[a[p]] = p;
            ++p;
        }
        ans[Q[i].id] = ask(p) - ask(Q[i].l - 1);
    }
    for(int i = 1;i<=m;++i) printf("%d\n",ans[i]);
    return 0;
}