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
char s[maxn];
int sum[maxn][26];
int T,n;
inline int solve(int l,int r,int c)
{
    if(l == r) return c != s[l];
    int mid = l + r >> 1;
    int left = solve(l,mid,c + 1),right = solve(mid + 1,r,c + 1);
    int lval = left + r - mid - (sum[r][c] - sum[mid][c]);
    int rval = right + (mid - l + 1) - (sum[mid][c] - sum[l - 1][c]);
    return std::min(lval,rval);
}
signed main()
{
    read(T);
    while(T--)
    {
        read(n);
        read(s + 1);
        for(int i = 1;i<=n;++i) s[i] -= 'a';
        for (int i = 1; i <= n; ++i) 
        {
            for (int j = 0; j < 26; ++j) sum[i][j] = sum[i - 1][j];
            sum[i][s[i]]++;
        }
        printf("%lld\n",solve(1,n,0));
    }
    return 0;
}