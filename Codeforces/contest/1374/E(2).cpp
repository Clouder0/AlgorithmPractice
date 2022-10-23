#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e6 + 100;
int n,k;
int A[maxn],B[maxn],C[maxn],acnt,bcnt,ccnt;
long long SA[maxn],SB[maxn],SC[maxn];
int main()
{
    read(n),read(k);
    for(int i = 1;i<=n;++i)
    {
        int t,a,b;
        read(t),read(a),read(b);
        if(a && b) C[++ccnt] = t;
        else if(a) A[++acnt] = t;
        else if(b) B[++bcnt] = t;
    }
    std::sort(A + 1,A + 1 + acnt);
    std::sort(B + 1,B + 1 + bcnt);
    std::sort(C + 1,C + 1 + ccnt);
    for(int i = 1;i<=acnt;++i) SA[i] = SA[i-1] + A[i];
    for(int i = 1;i<=bcnt;++i) SB[i] = SB[i-1] + B[i];
    for(int i = 1;i<=ccnt;++i) SC[i] = SC[i-1] + C[i];
    long long ans = 1ll << 60;
    for (int i = std::max(0,k - std::min(acnt, bcnt)); i <= ccnt && i <= k; ++i) 
        ans = std::min(ans, SA[k - i] + SB[k - i] + SC[i]);
    if (ans == 1ll << 60) puts("-1");
    else printf("%lld",ans);
    return 0;
}