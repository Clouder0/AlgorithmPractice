#include <cstdio>
#include <algorithm>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int t,n;
struct pack
{
    int x,y;
}all[1010];
bool cmp(const pack &a,const pack &b)
{
    if(a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}
int main()
{
    read(t);
    while(t--)
    {
        int lx = 0,ly = 0;
        read(n);
        for(int i = 1;i<=n;++i)
            read(all[i].x),read(all[i].y);
        sort(all+1,all+1+n,cmp);
        int maxh = 0;
        for(int i = 1;i<=n;++i)
        {
            if(maxh > all[i].y)
            {
                puts("NO");
                goto end;
            }
            maxh = all[i].y;
        }
        puts("YES");
        for(int i = 1;i<=n;++i)
        {
            for(;lx<all[i].x;++lx)
                putchar('R');
            for(;ly<all[i].y;++ly)
                putchar('U');
        }
        putchar('\n');
        end:;
    }
    return 0;
}