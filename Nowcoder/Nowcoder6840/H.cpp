#include <cstdio>
#include <cstring>
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
char s[maxn];
int main()
{
    scanf("%s",s + 1);
    int n = strlen(s + 1);
    int ans = 0;
    for (int i = 1; i <= n - 2; ++i) if(s[i] == 'o' && s[i+1] == 'r' && s[i+2] == 'a') ++ans;
    if(!ans) puts("yare yare daze");
    else printf("%d\n",ans);
    return 0;
}