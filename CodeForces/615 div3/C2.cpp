#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int t,n;
int main()
{
    read(t);
    while(t--)
    {
        read(n);
        for(int a = 2;a<=1000;++a)
        {
            if(n % a)
                continue;
            if(a*4 > n)
                break;
            for(int b = a+1;b<=100000;++b)
            {
                if(a * b > n)
                    break;
                if(a == b || (n / a) % b)
                    continue;
                int c = n / a / b;
                if(c < 2)
                    continue;
                if(a == b || b == c || a == c)
                    continue;
                printf("YES\n%d %d %d\n",a,b,c);
                goto end;
            }
        }
        puts("NO");
        end:;
    }
    return 0;
}