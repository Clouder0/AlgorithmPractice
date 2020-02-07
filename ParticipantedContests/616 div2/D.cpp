#include <cstdio>
#include <cstring>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,m;
char s[201000];
int all[300];
int main()
{
    scanf("%s",s+1);
    n = strlen(s);
    read(m);
    int l,r;
    while(m--)
    {
        memset(all,0,sizeof(all));
        int res = 0;
        read(l);
        read(r);
        if(l == r)
        {
            puts("Yes");
            goto end;
        }
        for(int i = l;i<=r;++i)
            ++all[s[i]-'a'];
        for(int i = 0;i<26;++i)
            if(all[i])
                ++res;
        if(res > 1)
            puts("Yes");
        else
            puts("No");
        end:;
    }
    return 0;
}