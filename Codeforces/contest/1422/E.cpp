#include <cstdio>
#include <algorithm>
#include <cstring>
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
const int maxn = 1e5 + 100;
char s[maxn];
int n, top, len[maxn], st[maxn],f[maxn];
char pre[maxn][12], last[maxn][3];
int main()
{
    read(s + 1);
    n = strlen(s + 1);
    for (int i = n; i; --i)
    {
        if(top && s[i] == s[st[top]])
        {
            if (f[i + 1] && st[top] == i + 1)  st[top--] = 0, f[i] = f[i + 2];
            else st[++top] = i, f[i] = f[i + 1];
        }
        else { st[++top] = i, f[i] = (s[st[top]] > s[st[top - 1]]); goto end; }

    end:
        len[i] = top;
        if(top > 10)
        {
            for (int j = 0; j < 5; ++j) pre[i][j] = s[st[top - j]];
            last[i][1] = s[st[1]], last[i][0] = s[st[2]];
        }
        else for (int j = 0; j < top; ++j) pre[i][j] = s[st[top - j]];
    }
    for (int i = 1; i <= n; ++i) 
    {
        printf("%d ",len[i]);
        if(len[i] > 10) printf("%s...%s\n",pre[i],last[i]);
        else printf("%s\n", pre[i]);
    }
    return 0;
}