#include <cstdio>
#include <cstdlib>
#include <ctime>
int ans[110];
int main()
{
    srand(time(0));
    puts("10");
    for (int t = 1; t <= 10; ++t) 
    {
        int n = 500;
        int M = ((1ll * rand() * rand()) % 1000000000) + 1;
        printf("%d\n",n);
        int now = 1;
        for (int i = 1; i <= n; ++i)
        {
            printf("%d ",now);
            now = (now * 2) % M;
        }
        puts("");
        ans[t] = M;
    }
    for (int i = 1; i <= 10; ++i) printf("%d\n",ans[i]);
    return 0;
}