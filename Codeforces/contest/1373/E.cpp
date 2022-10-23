
// Problem : E. Sum of Digits
// Contest : Codeforces - Educational Codeforces Round 90 (Rated for Div. 2)
// URL : https://codeforces.com/contest/1373/problem/E
// Memory Limit : 512 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

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
int T,n,k;
int f[200];
int main()
{
    read(T);
    for(int i = 1;i<=150;++i) for (int x = i; x; x /= 10) f[i] += x % 10;
    for(int i = 1;i<=150;++i) f[i] += f[i-1];
    while(T--)
    {
        read(n),read(k);
        if(f[k] == n)
        {
            puts("0");
            goto end;
        }
        for(int i = 1;i + k<=150;++i) if(f[i + k] - f[i-1] == n)
        {
            printf("%d\n",i);
            goto end;
        }
        puts("-1");
        end:;
    }
    return 0;
}