#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e5 + 100;
int n,k;
int A[maxn],B[maxn],C[maxn],acnt,bcnt,ccnt;
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
    int at = 0,bt = 0,pa = 1,pb = 1,pc = 1;
    long long ans = 0;
    while(at < k && bt < k && pa <= acnt && pb <= bcnt && pc <= ccnt)
    {
        if(C[pc] < A[pa] + B[pb]) ans += C[pc++],++at,++bt;
        else if(C[pc] >= A[pa] + B[pb]) ans += A[pa++] + B[pb++],++at,++bt;
    }
    while(at < k && pa <= acnt && pc <= ccnt)
    {
        if (C[pc] < A[pa]) ans += C[pc++], ++at, ++bt;
        else ans += A[pa++], ++at;
    }
    while(at < k && pa <= acnt) ans += A[pa++],++at;
    while(at < k && pc <= ccnt) ans += C[pc++],++at,++bt;
    while(bt < k && pb <= bcnt && pc <= ccnt)
    {
        if (C[pc] < B[pb]) ans += C[pc++], ++at, ++bt;
        else ans += B[pb++], ++bt;
    }
    while(bt < k && pb <= bcnt) ans += B[pb++],++bt;
    while(bt < k && pc <= ccnt) ans += C[pc++],++at,++bt;
    if(at < k || bt < k) puts("-1");
    else printf("%lld\n",ans);
    return 0;
}