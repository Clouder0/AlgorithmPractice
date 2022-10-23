#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
unsigned long long n,k;
int main()
{
    read(n);
    read(k);
    unsigned long long l,r,mid;
    l = 0,r = (1ull << n) - 1;
    if(n == 64)
        r = ~(1ull << 64);
    while(l < r)
    {
        mid = l + (r >> 1);
        if(k <= mid)
            putchar('0');
        else
            putchar('1'),k -= mid + 1,k = mid - k;
        r = mid;
    }
    return 0;
}