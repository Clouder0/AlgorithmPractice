#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int T,n,x;
char all[100010];
inline int gv(const char &c)
{
    return c=='0'?1:-1;
}
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        read(x);
        scanf("%s",all+1);
        int val = 0;
        for(int i = 1;i<=n;++i)
            val += gv(all[i]);
        if(val == 0)
        {
            if(x == 0)
            {
                printf("-1\n");
                continue;
            }
            val = 0;
            int ans = x==0?1:0;
            for(int i = 1;i<=n;++i)
            {
                val += gv(all[i]);
                if(val == x)
                    ++ans;
            }
            printf("%d\n",ans);
            continue;
        }
        int times = x / val;
        if(times <= 0)
        {
            val = 0;
            int ans = x==0?1:0;
            for(int i = 1;i<=n;++i)
            {
                val += gv(all[i]);
                if(val == x)
                    ++ans;
            }
            printf("%d\n",ans);
            continue;
        }
        if(times * val == x)
            --times;
        x -= times*val;
        val = 0;
        int ans = x==0?1:0;
        for(int i = 1;i<=n;++i)
        {
            val += gv(all[i]);
            if(val == x)
                ++ans;
        }
        for(int i = 1;i<=n;++i)
        {
            val += gv(all[i]);
            if(val == x)
                ++ans;
        }
        for(int i = 1;i<=n;++i)
        {
            val += gv(all[i]);
            if(val == x)
                ++ans;
        }
        printf("%d\n",ans);
    }
    return 0;
}