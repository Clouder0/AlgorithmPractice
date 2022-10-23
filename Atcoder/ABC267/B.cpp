#include <cstdio>
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
char s[20];
bool c[20];
int main()
{
    scanf("%s", s + 1);
    if (s[1] == '1') goto no;
    c[1] = (s[7] == '1');
    c[2] = (s[4] == '1');
    c[3] = (s[8] == '1' || s[2] == '1');
    c[4] = (s[1] == '1' || s[5] == '1');
    c[5] = (s[3] == '1' || s[9] == '1');
    c[6] = (s[6] == '1');
    c[7] = (s[10] == '1');
    for(int l = 1;l<7;++l)
        for(int r = l + 2;r <= 7;++r)
        {
            if(!c[l] || !c[r]) continue;
            int flag = 0;
            for(int k = l + 1;k<r;++k) if(c[k] == 0) flag = 1;
            if(flag) goto yes;
        }
    goto no;
    yes:
    puts("Yes");
    return 0;
    no:
    puts("No");
    return 0;
    }