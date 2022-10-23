
// Problem : C. Pluses and Minuses
// Contest : Codeforces - Educational Codeforces Round 90 (Rated for Div. 2)
// URL : https://codeforces.com/contest/1373/problem/C
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctype.h>
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
    for (; c != '+' && c != '-'; c = nc());
    for (; c == '+' || c == '-'; c = nc()) *s++ = c;
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
const int maxn = 1e6 + 100;
int T;
char s[maxn];
int sum[maxn],sum2[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(s + 1);
        int n = strlen(s + 1);
        for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + (s[i] == '+' ? 1 : -1);
        for (int i = 1; i <= n; ++i) sum2[i] = std::min(sum[i], sum2[i - 1]);
        int minn = sum2[1];
        for (int i = 2; i <= n; ++i) minn = minn > sum2[i] ? sum2[i] : minn;
        minn *= -1;
        long long ans = 0;
        for (int i = 1; i <= n; ++i) ans += (minn - std::max(0, -sum2[i]) + 1);
        printf("%lld\n", ans + minn);
    }
    return 0;
}