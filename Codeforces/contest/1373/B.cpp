
// Problem : B. 01 Game
// Contest : Codeforces - Educational Codeforces Round 90 (Rated for Div. 2)
// URL : https://codeforces.com/contest/1373/problem/B
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <cstdio>
#include <algorithm>
#include <ctype.h>
#include <cstring>
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
    for (; !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) *s++ = c;
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
const int maxn = 110;
int T;
char s[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(s + 1);
        int n = strlen(s + 1);
        int zero = 0,one = 0;
        for(int i = 1;i<=n;++i)  if(s[i] == '0') zero++; else one++;
        int turns = std::min(one,zero);
        if(turns % 2 == 0) puts("NET");
        else puts("DA");
    }
    return 0;
}