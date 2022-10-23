#include <cstdio>
int n;
int main()
{
    scanf("%d",&n);
    if(n == 1) puts("1.000000000");
    else     printf("%.9f", 1.0 / (n * n));
    return 0;
}