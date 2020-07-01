#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 60;
int T;
int n;
char s[maxn];
int a[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        scanf("%s",s+1);
        for(int i = 1;i<=n;++i) a[i] = (s[i] == '(' ? 1 : -1);
        int ans = 0;
        for(int i = 1;i<=n;++i)
        {
            int t = 0;
            for(int j = 1;j<=n;++j)
            {
                t += a[j];
                if(t < 0) 
                {
                    ++ans;
                    for(int k = j + 1;k<=n;++k) std::swap(a[k],a[k-1]);
                    break;
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}