#include <cstdio>
#include <algorithm>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c; r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
struct node
{
    int l,w;
}all[5100];
bool cmp(const node &a,const node &b)
{
    if(a.l == b.l)
        return a.w > b.w;
    return a.l > b.l;
}
int n,len;
int q[5100];
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
    {
        read(all[i].l);
        read(all[i].w);
    }
    sort(all+1,all+1+n,cmp);
    q[1] = all[1].w;
    len = 1;
    for(int i = 2;i<=n;++i)
    {
        if(all[i].w > q[len])
            q[++len] = all[i].w;
        else
            *lower_bound(q+1,q+1+len,all[i].w) = all[i].w;
    }
    printf("%d",len);
    return 0;
}