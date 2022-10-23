#include <cstdio>
#include <algorithm>
#include <set>
#include <ctype.h>
using namespace std;
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
const int maxn = 1e5  + 100;
int T,n, a[maxn];
set<int> S;
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        int zeronum = 0, pre = 0, res = n;
        for (int i = 1; i <= n; ++i) read(a[i]), zeronum += !a[i];
        //        for(int i = 1;i<=n;++i) printf("%d ",pre[i]);
        //        puts("");
        if (zeronum == n)
        {
            puts("0");
            goto end;
        }
        S.clear();
        S.insert(0);
        for (int i = 1; i <= n; ++i) 
        {
            pre ^= a[i];
            if (S.find(pre) != S.end())
                --res, S.clear(), S.insert(0), pre = 0;
            else S.insert(pre);
        }
        printf("%d\n", res);
        end:;
    }
    return 0;
}