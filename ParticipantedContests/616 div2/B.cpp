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
int n,t,top,tot;
int all[310000];
int main()
{
    read(t);
    while(t--)
    {
        read(n);
        for(int i = 1;i<=n;++i)
            read(all[i]);
        top = 0;
        for(int i = 1,tot = 0;i<=n;++i,++tot)
        {
            if(all[i] < tot)
                break;
            top = i;
        }
        bool flag = true;
        for(int i = n,tot = 0;i>top;--i)
        {
            if(all[i] < tot)
            {
                flag = false;
                break;
            }
            ++tot;
        }
        if(all[top] < n - top)
        {
            puts("No");
            goto end;
        }
        if(flag == 0)
            puts("No");
        else
            puts("Yes");
        end:;
    }
    return 0;
}