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
int T,n,a[maxn];
int one[40],zero[40];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        for(int i = 1;i<=n;++i) read(a[i]);
        for(int i = 0;i<=30;++i) one[i] = zero[i] = 0;
        for(int j = 0;j<=30;++j) for(int i = 1;i<=n;++i) if(a[i] & (1<<j)) one[j]++; else zero[j]++;
        for(int i = 30;i >= 0;--i) 
        {
            if((one[i] % 2) == 0) continue;
            if((one[i] % 4) == 3 && (zero[i] % 2) == 0)  puts("LOSE");
            else puts("WIN");
            goto end;
        }
        puts("DRAW");
        end:;
    }
    return 0;
}