#include <cstdio>
#include <cstring>
using namespace std;
char all[1000010];
int main()
{
    int len = 0;
    for(int i = 1;i>0;++i)
    {
        all[++len] = getchar();
        if (all[len] == 'W' || all[len] == 'L')
            continue;
        else if (all[len] == 'E')
        {
            --len;
            break;
        }
        --len;
    }
    int W = 0, L = 0;
    for (int i = 1; i <= len; ++i)
    {
        if (all[i] == 'W')
            ++W;
        else
            ++L;
        if ((W >= 11 || L >= 11) && (W - L >= 2 || L - W >= 2))
            printf("%d:%d\n", W, L), W = L = 0;
    }
    printf("%d:%d\n", W, L);
    printf("\n");
    W = L = 0;
    for (int i = 1; i <= len; ++i)
    {
        if (all[i] == 'W')
            ++W;
        else
            ++L;
        if ((W >= 21 || L >= 21) && (W - L >= 2 || L - W >= 2))
            printf("%d:%d\n", W, L), W = L = 0;
    }
    printf("%d:%d\n", W, L);
    return 0;
}