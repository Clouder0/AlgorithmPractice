#include <cstdio>
#include <algorithm>
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
int n,a[maxn];
int left[maxn],right[maxn];
int main()
{
    while(1)
    {
        read(n);
        if(n == 0) return 0;
        for (int i = 1; i <= n; ++i) read(a[i]),left[i] = right[i] = i;
        for (int i = 1; i <= n; ++i) while (left[i] > 1 && a[i] <= a[left[i] - 1]) left[i] = left[left[i] - 1];
        for (int i = n; i >= 1; --i) while (right[i] < n && a[i] <= a[right[i] + 1]) right[i] = right[right[i] + 1];
        long long ans = 0;
        for (int i = 1; i <= n; ++i) ans = std::max(ans,1ll * a[i] * (right[i] - left[i] + 1));
        printf("%lld\n",ans);
    }
    return 0;
}