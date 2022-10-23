#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 21;
int n,a[maxn];
int gcd(int a,int b){return !b ? a : gcd(b,a%b);}
int main()
{
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    int g = a[1];
    for (int i = 2; i <= n; ++i) g = gcd(g, std::abs(a[i]));
    printf("%d\n",g);
    return 0;
}
