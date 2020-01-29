#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n;
int sum;
int num[11];
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
    {
        int temp;
        read(temp);
        ++num[temp];
        sum += temp;
    }
    for(int i = 1;i<=10;++i)
        for(int j = 1;j<=10;++j)
            if((sum - i - j) % 10 == 0)
            {
                --num[i],--num[j];
                if(num[i] >= 0 && num[j] >= 0)
                {
                    if((i+j) % 10 == 0)
                        puts("10");
                    else
                        printf("%d",(i+j)%10);
                    return 0;
                }
                ++num[i],++num[j];
            }
    putchar('0');
    return 0;
}