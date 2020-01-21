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
const int maxn = 1e5 + 10;
int n,X;
struct node
{
    int l,r,val,id;
    bool operator<(const node b) const
    {
        if((X - val) * r != (X - b.val) * b.r)
            return (X - val) * r > (X - b.val) * b.r;
        return r > b.r;
    }
}all[maxn];
int c[maxn];
int T,XB,NB;
int main()
{
    read(n);
    read(X);
    for(int i = 1;i<=n;++i)
        all[i].id = i,read(all[i].val),read(all[i].l),read(all[i].r);
    sort(all+1,all+1+n);
    for(int i = 1;i<=n;++i)
        XB += all[i].l * all[i].val;
    int last = n;
    for(int i = 1;i<=n;++i)
    {
        XB += (all[i].r - all[i].l) * all[i].val;
        NB += all[i].r * X;
        T += X;
        if(NB >= XB)
        {
            last = i;
            break;
        }
    }
    int ans = last * X;
    for(int i = 1;i<=last;++i)
    {
        int time;
        NB -= all[i].r * X;
        int delta = XB - NB;
        if(delta < 0)
            goto end;
        time = delta / all[i].r;
        if(time * all[i].r < delta)
            ++time;
        if(T - X + time < ans)
            ans = T - X + time;
        end:
        NB += all[i].r * X;
    }
    printf("%d",ans);
    return 0;
}