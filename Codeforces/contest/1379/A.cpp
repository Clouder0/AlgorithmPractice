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
    for (; c != '?' && !isalpha(c); c = nc());
    for (; c == '?' || isalpha(c); c = nc()) *s++ = c;
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
const int maxn = 60;
int T;
int n;
char s[maxn];
int save[maxn];
char t[maxn];
//abacaba
int main()
{
    t[1] = 'a',t[2] = 'b',t[3] = 'a',t[4] = 'c',t[5] = 'a',t[6] = 'b',t[7] = 'a';
    read(T);
    while(T--)
    {
        read(n);
        read(s + 1);
        int ans = 0;
        for(int i = 1;i<=n - 6;++i)
        {
            bool flag = 1;
            for(int j = 1;flag && j<=7;++j) if(!(s[i + j - 1] == t[j])) flag = 0;
            ans += flag;
        }
        if(ans > 1){puts("No");goto end;}
        if(ans == 1)
        {
            puts("Yes");
            for (int i = 1; i <= n; ++i) if(s[i] == '?') putchar('z'); else putchar(s[i]);
            putchar('\n');
            goto end;
        }
        for(int i = 1;i<=n;++i)
        {
            bool flag = 1;
            for(int j = 1;j<=7;++j) if(!(s[i+j-1] == t[j] || s[i+j-1] == '?')) flag = 0;
            if(flag)
            {
                for (int j = 1; j <= 7; ++j) save[i+j-1] = s[i+j-1],s[i + j - 1] = t[j];
                int cnt = 0;
                for(int k = 1;k<=n;++k)
                {
                    bool f = 1;
                    for(int p = 1;p<=7;++p) if(s[k+p-1] != t[p]) f = 0;
                    if(f) ++cnt;
                }
                if(cnt == 1)
                {
                    puts("Yes");
                    for(int k = 1;k<=n;++k) if(s[k] == '?') putchar('z'); else putchar(s[k]);
                    putchar('\n');
                    goto end;
                }
                for (int j = 1; j <= 7; ++j) s[i + j - 1] = save[i + j - 1];
            }
        }
        puts("No");
        end:;
    }
    return 0;
}