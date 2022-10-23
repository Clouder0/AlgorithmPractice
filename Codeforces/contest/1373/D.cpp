
// Problem : D. Maximum Sum on Even Positions
// Contest : Codeforces - Educational Codeforces Round 90 (Rated for Div. 2)
// URL : https://codeforces.com/contest/1373/problem/D
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <cstdio>
#include <algorithm>
#include <ctype.h>
#define int long long
const int bufSize = 1e6;
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
const int maxn = 2e5 + 100;
int T,n;
int a[maxn];
int sum[maxn][2];
int maxl[maxn][2],maxr[maxn][2];
signed main()
{
    read(T);
    while(T--)
    {
        read(n);
        for (int i = 0; i < n; ++i) read(a[i]);
        sum[0][0] = a[0];
        for (int i = 1; i < n; ++i) sum[i][0] = sum[i - 1][0] + ((i & 1) ^ 1) * a[i], sum[i][1] = sum[i - 1][1] + (i & 1) * a[i];
//        for(int i = 0;i<n;++i) printf("%d ",sum[i][0]);
//        putchar('\n');
//        for(int i = 0;i<n;++i) printf("%d ",sum[i][1]);
//        putchar('\n');
        for (int i = 1; i < n; ++i) 
        {
            maxl[i][0] = maxl[i-1][0],maxl[i][1] = maxl[i-1][1];
            if (i & 1) maxl[i][1] = std::max(sum[i - 1][0] - sum[i - 1][1], maxl[i][1]);
            else maxl[i][0] = std::max(sum[i - 1][0] - sum[i - 1][1], maxl[i][0]);
//            printf("%d %d %d\n",i,maxl[i][0],maxl[i][1]);
        }
        int ans = 0;
        int tans = sum[n - 1][0];
//        printf("tans: %d\n",tans);
        for (int i = 0; i < n; ++i) ans = std::max(ans,sum[i][1] - sum[i][0] + maxl[i][1 ^ (i & 1)]);
//        printf("ans: %d\n",ans);
        printf("%lld\n",tans + ans);
    }
    return 0;
}