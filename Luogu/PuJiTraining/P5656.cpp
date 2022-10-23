#include <cstdio>
#include <algorithm>
#define int long long
int T, a, b, c;
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
void exgcd(int a, int b, int& x, int& y)
{
    if (b == 0) return (void)(x = 1, y = 0);
    exgcd(b, a % b, y, x), y -= x * (a / b);
}
signed main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&a,&b,&c);
        int g,x,y;
        g = gcd(a,b);
        if (c % g) { puts("-1"); continue; }
        a /= g, b /= g;
        exgcd(a, b, x, y);
//        printf("exgcd:%d %d\n",x,y);
        x *= c / g, y *= c / g;//ax + by = c
//        printf("real:%d %d\n",x,y);
        int xmin = ((x % b) + b) % b;
        int ymin = ((y % a) + a) % a;
        if(xmin == 0) xmin = b; if(ymin == 0) ymin = a;
        int xmax = (c - ymin * b * g) / (a * g);
        int ymax = (c - xmin * a * g) / (b * g);
        if(ymax <= 0) printf("%d %d\n",xmin,ymin);
        else printf("%d %d %d %d %d\n",(xmax - xmin) / b + 1,xmin,ymin,xmax,ymax);
    }
    return 0;
}