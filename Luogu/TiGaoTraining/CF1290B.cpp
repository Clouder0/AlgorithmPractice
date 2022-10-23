#include <cstdio>
#include <cstring>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e5 + 100;
char s[maxn];
int n,q,l,r;
int a[maxn][26];
int main()
{
    scanf("%s",s+1);
    n = strlen(s+1);
    for(int i = 1;i<=n;++i)
    {
        for(int j = 0;j<26;++j) a[i][j] = a[i-1][j];
        a[i][s[i]-'a']++;
    }
    read(q);
    while(q--)
    {
        read(l),read(r);
        int t = 0;
        if(s[l] != s[r])
            goto YES;
        else if(l == r)
            goto YES;
        for(int i = 0;i<26;++i) if(a[r][i] - a[l-1][i]) ++t;
        if(t >= 3)
            goto YES;
        goto NO;
        YES:
        puts("YES");
        continue;
        NO:
        puts("NO");
        continue;
    }
    return 0;
}