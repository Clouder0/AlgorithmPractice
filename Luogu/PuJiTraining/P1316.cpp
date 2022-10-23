#include <cstdio>
#include <algorithm>
using namespace std;
void read(int &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,m;
int pos[100010];
inline bool check(const int &mindis)
{
    int last = 1,num = 1;
    for(int i = 2;i<=n;++i)
    {
        if(pos[i] - pos[last] >= mindis)
        {
            ++num;
            last = i;
        }
    }
    return num >= m;
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
        read(pos[i]);
    sort(pos+1,pos+1+n);
    int ll = pos[n],rr = pos[n],mid,ans;
    for(int i = 2;i<=n;++i)
        ll = ll > pos[i] - pos[i-1] ? pos[i] - pos[i-1] : ll;
    while(ll<=rr)
    {
        mid = (ll+rr)>>1;
        if(check(mid))
        {
            ans = mid;
            ll = mid + 1;
        }
        else
            rr = mid - 1;
    }
    printf("%d",ans);
    return 0;
}