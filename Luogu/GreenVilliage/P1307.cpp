#include <cstdio>
using namespace std;
int n;
int main()
{
    scanf("%d", &n);
    bool flag = true;
    if (n < 0)
        n = -n, putchar('-');
    while (n)
    {
        if (flag && n % 10)
            putchar(n % 10 + '0'), flag = false;
        else if (!flag)
            putchar(n % 10 + '0');
        n /= 10;
    }
    return 0;
}