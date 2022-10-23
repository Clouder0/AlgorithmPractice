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
const int maxn = 110;
int T;
int n;
struct node
{
    int p,c;
}a[maxn];
bool cmp(const node &a,const node &b)
{
    if(a.c == b.c)
        return a.p < b.p;
    return a.c < b.c;
}
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        for(int i = 1;i<=n;++i)
            read(a[i].p),read(a[i].c);
        for(int i = 1;i<=n;++i)
        {
            if(a[i].c > a[i].p)
            {
                puts("NO");
                goto end;
            }
            if(a[i].c < a[i-1].c)
            {
                puts("NO");
                goto end;
            }
            if(a[i].p < a[i-1].p)
            {
                puts("NO");
                goto end;
            }
            if(a[i].c - a[i-1].c > a[i].p - a[i-1].p)
            {
                puts("NO");
                goto end;
            }
        }
        puts("YES");
        end:;
    }
    return 0;
}