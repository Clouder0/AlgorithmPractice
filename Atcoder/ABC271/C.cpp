#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <ctype.h>
using namespace std;
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
const int maxn = 5e5 + 100;
int n,a[maxn];
set<int> mp;
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]), mp.insert(a[i]);
    int ans = 0;
    int need = 2 - (mp.find(ans + 1) != mp.end());
    while(n >= need)
    {
        ++ans;
        n -= need;
        need = 2 - (mp.find(ans + 1) != mp.end());
    }
    printf("%lld\n", ans);
    return 0;
}