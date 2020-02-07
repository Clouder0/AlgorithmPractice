#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,t;
char all[3100];
int main()
{
    read(t);
    while(t--)
    {
        read(n);
        scanf("%s",all+1);
        int one = 0,two = 0;
        for(int i = 1;i<=n;++i)
        {
            if(all[i] % 2)
            {
                if(one == 0)
                    one = all[i];
                else
                {
                    two = all[i];
                    putchar(one),putchar(two),putchar('\n');
                    goto end;
                }
            }
        }
        puts("-1");
        end:;
    }
    return 0;
}