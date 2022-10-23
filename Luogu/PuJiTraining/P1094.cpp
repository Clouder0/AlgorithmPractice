#include <cstdio>
using namespace std;
int w, n;
int all[201];
int main()
{
    scanf("%d%d", &w, &n);
    int temp;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &temp);
        ++all[temp];
    }
    int ans = 0;
    for (int i = w; i >= 5; --i)
    {
        while (all[i])
        {
            ++ans;
            --all[i];//应当先减去这一个，以免只有1个时仍被重复选择
            for (int j = w - i; j >= 5; --j)
            {
                if (all[j])
                {
                    --all[j];
                    break;
                }
            }            
        }
    }
    printf("%d", ans);
    return 0;
}