#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;
#define DEBUG
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
const int maxn = 1e6 + 100;
int n,a[maxn],s[maxn],top;
long long f[maxn];
int main()
{
    read(n);
    for (int i = 1; i < n; ++i) read(a[i]);
    long long res = 1;
    f[n - 1] = 1, s[++top] = n - 1;
    for (int i = n - 2; i > 0; --i)
    {
        int l = 1,r = top,mid,ans = 0;
        while(l <= r)
        {
            mid = l + r >> 1;
            if(s[mid] <= a[i]) ans = mid,r = mid - 1;
            else l = mid + 1;
        }
        res += (f[i] = f[s[ans]] + s[ans] - i + n - a[i]);
        while(top && a[s[top]] <= a[i]) --top;
        s[++top] = i;
    }
    printf("%lld\n",res);
    return 0;
}