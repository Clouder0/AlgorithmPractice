#include <cstdio>
#include <memory.h>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int q,x,cnt,times;
int all[500000];
int f[500000];
int main()
{
    read(q);
    read(x);
    int ll = 0;
    while(q--)
    {
        int t;
        read(t);
        if(t < x)
            cnt += f[t] == 0,++f[t];
        else
            cnt += f[t%x] == 0,++f[t%x];
        while(cnt == x)
        {
            for(int i = 0;i<x;++i)
                --f[i];
            ll = cnt = 0,++times;
            for(int i = 0;i<x;++i)
                cnt += f[i] != 0;
            for(;ll<x;++ll)
                if(f[ll] == 0)
                    break;
        }
        for(;ll<x;++ll)
            if(f[ll] == false)
            {
                printf("%d\n",ll + x * times);
                break;
            }
    }
    return 0;
}