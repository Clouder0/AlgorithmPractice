#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
const int maxn = 2e5 + 100;
int T,n,l;
int a[maxn];
long double ltime[maxn],rtime[maxn];
const double eps = 1e-4;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&l);
        for (int i = 1; i <= n; ++i) scanf("%d",a + i);
        for (int i = 0; i <= n + 1; ++i) ltime[i] = rtime[i] = 0;
        a[n + 1] = l;
        for (int i = 1; i <= n + 1; ++i) ltime[i] = ltime[i - 1] + (a[i] - a[i - 1]) / (1.0 * i);
        for (int i = n; i >= 0; --i) rtime[i] = rtime[i + 1] + (a[i + 1] - a[i]) / (1.0 * (n - i + 1));
        for (int i = 0; i <= n; ++i)
        {
            //meet in i->i+1
            long double lt = ltime[i], rt = rtime[i + 1];
            long double ls = 1.0 * (i + 1.0), rs = 1.0 * (n - i + 1.0);
            long double lpos = 1.0 * a[i], rpos = 1.0 * a[i + 1];
            if (lt < rt)
            {
                long double e = rt - lt;
                lt = rt;
                lpos += e * ls;
                if(rpos - lpos < -eps) continue;
            }
            if (rt < lt)
            {
                long double e = lt - rt;
                rt = lt;
                rpos -= e * rs;
                if(rpos - lpos < -eps) continue;
            }
            long double extra = (1.0 * (rpos - lpos)) / (ls + rs);
            printf("%.8f\n",(double)(rt + extra));
            goto end;
        }
        printf("???");
        end:;
    }
    return 0;
}