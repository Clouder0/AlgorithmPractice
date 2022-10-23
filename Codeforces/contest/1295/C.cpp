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
int T;
char s[100100],t[100100];
int dp[100100];
int main()
{
    read(T);
    while(T--)
    {
        memset(dp,0,sizeof(dp));
        scanf("%s",s+1);
        scanf("%s",t+1);
        int sl = strlen(s+1);
        int tl = strlen(t+1);
        int has[300];
        for(int i = 1;i<=tl;++i)
            has[t[i]] = true;
        for(int i = 1;i<=sl;++i)
            has[s[i]] = false;
        for(int i = 1;i<=256;++i)
            if(has[i])
            {
                printf("-1\n");
                goto end;
            }
        for(int i = 1;i<=sl;++i)
        {
        }
        end:;
    }
    return 0;
}