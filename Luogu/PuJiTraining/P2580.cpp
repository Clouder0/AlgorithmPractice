#include <cstdio>
#include <cstring>
const int maxn = 5e5 + 100;
int to[maxn][26], cnt;
bool end[maxn], mark[maxn];
int n, m;
char s[100];
void ins(char *s)
{
    int p = 0;
    for(;*s != '\0';++s)
    {
        int c = *s - 'a';
        if(!to[p][c]) to[p][c] = ++cnt;
        p = to[p][c];
    }
    end[p] = 1;
}
int find(char *s)
{
    int p = 0;
    for(;*s != '\0';++s)
    {
        int c = *s - 'a';
        if(!to[p][c]) return 0;
        p = to[p][c];
    }
    if(!end[p]) return 0;
    if(mark[p]) return 2;
    return mark[p] = 1;
}
int main()
{
    scanf("%d",&n);
    for(int i = 1;i<=n;++i) scanf("%s",s + 1),ins(s + 1);
    scanf("%d",&m);
    for(int i = 1;i<=m;++i)
    {
        scanf("%s", s + 1);
        int res = find(s + 1);
        if (res == 0) puts("WRONG");
        else if (res == 1) puts("OK");
        else puts("REPEAT");
    }
    return 0;
}