#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
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
const int maxn = 1000;
int T,n;
int a[maxn],cnt[maxn];
int main()
{
    read(T);
    while(T--)
    {
        int ans = 0;
        read(n);
        for (int i = 1; i <= n; ++i) read(a[i]);
        memset(cnt,0,sizeof(cnt));
        for(int i = 1;i<=n;++i)
        {
            for(int j = 1;j<i;++j)
            {
                int s = a[i] + a[j];
                for (int k = 1; k <= n; ++k) cnt[a[k]] = 0;
                int res = 0;
                for (int k = 1; k <= n; ++k)
                {
                    if (s - a[k] >= 0 && cnt[s - a[k]]) cnt[s - a[k]]--, ++res;
                    else cnt[a[k]]++;
                }
                ans = std::max(ans,res);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}