#include <cstdio>
int ppp;
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar())
    {
        if(c == '-')
        {
            ppp = 1;
            return;
        }
    }
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
unsigned long long O;
void print(unsigned long long x)
{
    if(x >= 10)
        print(x / 10);
    putchar((x % 10) + 48);
}
int main()
{
    read(O);
    if(O <= 0 || ppp)
    {
        puts("0");
        return 0;
    }
    O = (O - 1) * 2 + 1;
    print(O);
    return 0;
}