#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 10;
int all[maxn];
int n;
int has[50];
int main()
{
    read(n);
    int temp;
    for(int i = 1;i<=n;++i)
    {
        read(temp);
        int p = 0;
        while(temp)
        {
            has[p] += temp & 1;
            ++p;
            temp >>= 1;
        }
    }
    int ans = 0;
    for(int i = 0;i<50;++i)
        if(has[i] == 0)
        {
            continue;
        }
        else if(has[i] >= (n >> 1))
        {
            ans += 1<<i;
        }
    printf("%d",ans);
    return 0;
}