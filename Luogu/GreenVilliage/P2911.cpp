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
const int maxn = 1000;
int a,b,c;
int times[maxn];
int main()
{
    read(a),read(b),read(c);
    for (int i = 1; i <= a; ++i)  for(int j = 1;j<=b;++j) for(int k = 1;k<=c;++k) times[i + j + k]++;
    int ans = 3;
    for(int i = 3;i<=a+b+c;++i) if(times[i] > times[ans]) ans = i;
    printf("%d\n",ans);
    return 0;
}