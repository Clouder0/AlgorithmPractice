#include <cstdio>
#include <algorithm>
#define int long long
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e6 + 100;
struct node
{
    int t,pos;
}A[maxn];
int n,d,ans = 1ll<<60;
int queue[maxn],head,tail;
bool cmp(const node &a,const node &b){return a.pos < b.pos;}
signed main()
{
    read(n),read(d);
    for(int i = 1;i<=n;++i) read(A[i].pos),read(A[i].t);
    std::sort(A + 1,A + 1 + n,cmp);
    head = 1,tail = 0;
    for(int i = 1;i<=n;++i)
    {
        while (tail > head && A[i].t - A[queue[head + 1]].t >= d) ++head;
        int L = A[i].pos - A[queue[head]].pos;
        int T = std::abs(A[i].t - A[queue[head]].t);
        if(T >= d && L < ans) ans = L;
        while(tail >= head && A[i].t <= A[queue[tail]].t) --tail;
        queue[++tail] = i;
    }
    if(ans == 1ll<<60) puts("-1");
    else printf("%lld",ans);
    return 0;
}