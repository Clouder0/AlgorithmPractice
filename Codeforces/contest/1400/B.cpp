#include <cstdio>
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
const int maxn = 4e5 + 100;
int T,cnts,cntw,s,w,p,f;
int main()
{
    read(T);
    while(T--)
    {
        read(p),read(f);
        read(cnts),read(cntw);
        read(s),read(w);
        if(s > w) std::swap(s,w),std::swap(cnts,cntw);
        long long res = 0;
        for(int i = 0;i<=cnts;++i)
        {
            if(1ll * i * s > p) break;
            int takew = (p - i * s) / w;
            long long ans = i + takew;
            int lefts = cnts - i,leftw = cntw - takew;
            int takes = std::min(lefts,f / s);
            ans += takes + std::min(leftw,(f - s * takes) / w);
            res = std::max(ans,res);
        }
        printf("%lld\n",res);
    }
    return 0;
}