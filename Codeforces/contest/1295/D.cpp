#pragma GCC target("avx")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <cstdio>
#include <vector>
#include <set>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int T;
long long a,b;
inline long long gcd(const long long x,const long long y)
{
    if(y == 0)
        return x;
    return gcd(y,x%y);
}
long long solve(long long r,  long long n) {
    vector<long long>p;
    p.clear();
    for(long long i = 2; i*i <= n; ++i) {
        if(n % i == 0) {
            p.push_back(i);
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) p.push_back(n); //可能n也是素数
    long long sum = 0;
    for(long long msk = 1; msk < (1<<p.size()); ++msk) {
        long long mult = 1, bits = 0;
        for(int i = 0; i < p.size(); ++i) {
            if(msk & (1<<i)) { //选择了第i个素数因子 
                bits++; 
                mult *= p[i];
            }
        }
        long long cur = r / mult;
        if(bits & 1) sum += cur;
        else sum -= cur;
    } 
    return r - sum;
}
int main()
{
    read(T);
    while(T--)
    {
        read(a);
        read(b);
        long long p = gcd(a,b);
        int ans = 0;
        long long rr = (a + b - 1) / p;
        a /= p;
        b /= p;
        printf("%lld\n",solve(rr,b) - solve(a-1,b));
    }
    return 0;
}