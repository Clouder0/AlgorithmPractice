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
        //如果补差补不完则全部补差，否则先补齐，然后均分
        if(delta >= all[1])
        {
            ans += all[1];
            all[3] -= all[1];
            ans += all[2];
        }
        else
        {
            ans += delta;
            all[1] -= delta;
            ans += (all[1] >> 1) << 1;
            ans += all[2] - ((all[1]) >> 1);
        }
        printf("%d\n",ans);
    }
    return 0;
}