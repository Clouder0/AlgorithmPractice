#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int d,n;
int A[150][150];
int main()
{
    read(d);
    read(n);
    for(int i = 1;i<=n;++i)
    {
        int a,b,c;
        read(a),read(b),read(c);
        A[a][b] = c;
    }
    long long maxa = 0,ans = 0;
    for(int i = 0;i<=128;++i)
        for(int j = 0;j<=128;++j)
        {
            int num = 0;
            for(int k = i - d;k<=i+d;++k)
                for(int p = j-d;p<=j+d;++p)
                    if(k >= 0 && k <= 128 && p >= 0 && k <= 128)
                        num += A[k][p];
            if(num > maxa)
                ans = 1,maxa = num;
            else if(num == maxa)
                ++ans;
        }
    printf("%lld %lld",ans,maxa);
    return 0;
}