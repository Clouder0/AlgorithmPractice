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
int T;
int n,m,k;
int all[4000];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        read(m);
        read(k);
        for(int i = 1;i<=n;++i)
            read(all[i]);
        if(k >= m)
            k = m - 1;
        int ans = 0;
        for(int l = 0;l<=k;++l)
        {
            int res = 1<<30;
            int r = k - l;
            int left = m - 1 - l - r;
            //i个人取前，k-i+1个人取后
            //还有m-k+1个人可以取
            //[1,l]取完，[n-r+1,n]取完
            //剩余人数可能取left个
            for(int ll = 0;ll<=left;++ll)
            {
                int rr = left - ll;
                res = min(res,max(all[l+ll+1],all[n-r-rr]));
            }
            ans = max(ans,res);
        }
        printf("%d\n",ans);
    }
    return 0;
}