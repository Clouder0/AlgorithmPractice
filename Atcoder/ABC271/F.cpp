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
#include <algorithm>
#include <map>
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
const int maxn = 30;
int n, a[maxn][maxn];
map<int, long long> mp[maxn][maxn];
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) read(a[i][j]);
    mp[1][1][a[1][1]] = 0;
    int xorsum = a[1][1];
    for (int i = 2; i <= n; ++i) 
    {
        xorsum ^= a[1][i];
        mp[1][i][xorsum] = 1;
    }
    xorsum = a[1][1];
    for(int i = 2;i<=n;++i)
    {
        xorsum ^= a[i][1];
        mp[i][1][xorsum] = 1;
    }
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 2; j <= n; ++j)
        {
            for (map<int, long long>::iterator it = mp[i - 1][j].begin(); it != mp[i - 1][j].end(); ++it)
            {
                map<int, long long>::iterator now = mp[i][j].find(a[i][j] ^ it->first);
                if (now == mp[i][j].end())
                    mp[i][j][a[i][j] ^ it->first] = it->second;
                else
                    now->second += it->second;
            }
            for (map<int, long long>::iterator it = mp[i][j-1].begin(); it != mp[i][j-1].end(); ++it)
            {
                map<int, long long>::iterator now = mp[i][j].find(a[i][j] ^ it->first);
                if (now == mp[i][j].end())
                    mp[i][j][a[i][j] ^ it->first] = it->second;
                else
                    now->second += it->second;
            }

        }
    }
    if (mp[n][n].find(0) == mp[n][n].end())
        puts("0");
    else
        printf("%lld\n", mp[n][n][0]);
    return 0;
}