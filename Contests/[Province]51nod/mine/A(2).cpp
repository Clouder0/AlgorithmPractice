#include <cstdio>
#include <algorithm>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 10;
int n,X;
struct node
{
    int l,r,val,id;
    bool operator<(const node b) const
    {
        return r > b.r;
    }
}all[maxn];
int c[maxn];
int Lsum[maxn],Rsum[maxn],XBDsum[maxn];
int T,XB,NB;
int last,chooseRange,ansT = 0x3f3f3f3f;
inline void choose(int XXB,int NNB)
{
    XXB += XBDsum[last] - XBDsum[last - 1];
    int delta = XXB - NNB;
    int time = delta / all[last].r;
    if(time * all[last].r < delta)
        ++time;
    T += time;
    if(T < ansT)
        ansT = T;
    T -= time;
}
void dfs(int p,int XXB,int NNB)
{
    if(T > ansT || p > n)
        return;
    if(XXB > NNB && XXB - NNB <= chooseRange)
    {
        choose(XXB,NNB);
        dfs(p+1,XXB - XBDsum[p] + XBDsum[p-1],NNB - X * all[p].r);
    }
    XXB += XBDsum[p] - XBDsum[p-1];
    NNB += X * all[p].r;
    T += X;
    if(XXB > NNB && XXB - NNB <= chooseRange)
    {
        choose(XXB,NNB);
        dfs(p+1,XXB,NNB);
    }
    T -= X;
}
int main()
{
    read(n);
    read(X);
    for(int i = 1;i<=n;++i)
        all[i].id = i,read(all[i].val),read(all[i].l),read(all[i].r),Lsum[i] = Lsum[i-1]+ all[i].l,Rsum[i] = Rsum[i-1] + all[i].r;
    sort(all+1,all+1+n);
    for(int i = 1;i<=n;++i)
        XB += all[i].l * all[i].val,XBDsum[i] = XBDsum[i-1] + (all[i].r - all[i].l) * all[i].val;
    for(int i = 1;i<=n;++i)
    {
        T = 0;
        chooseRange = all[i].r * X - (all[i].r-all[i].l) * all[i].val;
        if(X * Rsum[i] > XB + XBDsum[i])
        {
            //如果可以在前面解决，直接乱搞
            last = i;
            dfs(1,XB,NB);
            continue;
        }
        XB += XBDsum[i-1];
        NB += X * Rsum[i-1];
        last = i;
        dfs(i + 1,XB,NB);
        XB -= XBDsum[i-1];
        NB -= X * Rsum[i-1];
    }
    printf("%d",ansT);
    return 0;
}