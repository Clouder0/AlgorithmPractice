#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast","-funroll-loops")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
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
#include <bitset>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e5 + 100;
int T,n;
char a[maxn],b[maxn];
int l,r,ll,rr;
vector<bool> aa,bb;
char c[maxn];
int ans[maxn],k;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        aa.clear(),bb.clear();
        k = 0;
        scanf("%d",&n);
        scanf("%s",a + 1),scanf("%s",b + 1);
//        for (int i = 1; i <= n; ++i) aa.push_back(a[i] == '1'),bb.push_back(b[i] == '1');
        for(int i = 1;i<=n;++i) a[i] -= 48,b[i] -= 48;
        l = 1,r = n,ll = 1,rr = n;
        int valflag = 0,posflag = 0,pre = 0;
        while(l <= r)
        {
            if(valflag == 0 && posflag == 0)
            {
                while(r >= l && a[r] == b[rr]) --r,--rr;
                if(r < l) break;
                int t = r - l + 1;
                if(a[l] == b[rr]) ans[++k] = 1,++l,--rr;
                ans[++k] = pre + t;
                valflag ^= 1,posflag ^= 1;
            }
            else if(valflag == 1 && posflag == 1)
            {
                while(r >= l && a[l] != b[rr]) ++l,--rr;
                if(r < l) break;
                int t = r - l + 1;
                if(a[r] != b[rr]) ans[++k] = 1,--r,--rr;
                ans[++k] = pre + t;
                valflag ^= 1,posflag ^= 1;
            }
        }
        printf("%d ",k);
        for(int i = 1;i<=k;++i) printf("%d ",ans[i]);
        putchar('\n');
    }
    return 0;
}