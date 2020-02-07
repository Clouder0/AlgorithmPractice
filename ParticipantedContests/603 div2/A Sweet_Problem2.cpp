#include <cstdio>
#include <algorithm>
using namespace std;
int all[4];
int ans, t;
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        ans = 0;
        for (int i = 1; i <= 3; ++i)
            scanf("%d", all + i);
        sort(all + 1, all + 4);
        int delta = all[3] - all[2];
        if (delta >= all[1])
            printf("%d\n", all[1] + all[2]);
        else
            printf("%d\n",(all[1] + all[2] + all[3])>>1);
    }
    return 0;
}