#include <cstdio>
#include <cstring>
using namespace std;
int p1, p2, p3;
char all[100000];
int main()
{
    scanf("%d%d%d", &p1, &p2, &p3);
    scanf("%s", all + 1);
    int n = strlen(all + 1), temp1, temp2;
    for (int i = 1; i <= n; ++i)
    {
        if (all[i] == '-')
        {
            if (!((all[i - 1] >= '0' && all[i + 1] >= '0' && all[i - 1] <= '9' && all[i + 1] <= '9' && all[i + 1] > all[i - 1]) || (all[i - 1] >= 'a' && all[i + 1] >= 'a' && all[i - 1] <= 'z' && all[i + 1] <= 'z' && all[i + 1] > all[i - 1])))
            {
                putchar('-');
                continue;
            }
            if (all[i - 1] >= '0' && all[i - 1] <= '9')
            {
                if (p3 == 1)
                {
                    for (int j = all[i - 1] + 1; j < all[i + 1]; ++j)
                        for (int k = 1; k <= p2; ++k)
                            putchar((p1 != 3 ? j : '*'));
                }
                else
                {
                    for (int j = all[i + 1] - 1; j > all[i - 1]; --j)
                        for (int k = 1; k <= p2; ++k)
                            putchar((p1 != 3 ? j : '*'));
                }
                continue;
            }
            temp1 = all[i - 1] - 'a' >= 0 ? all[i - 1] - 'a' : all[i - 1] - 'A';
            temp2 = all[i + 1] - 'a' >= 0 ? all[i + 1] - 'a' : all[i + 1] - 'A';
            if (p1 == 1)
            {
                if (p3 == 1)
                {
                    for (int j = temp1 + 'a' + 1; j < temp2 + 'a'; ++j)
                        for (int k = 1; k <= p2; ++k)
                            putchar(j);
                }
                else
                {
                    for (int j = temp2 + 'a' - 1; j > temp1 + 'a'; --j)
                        for (int k = 1; k <= p2; ++k)
                            putchar(j);
                }
            }
            else if (p1 == 2)
            {
                if (p3 == 1)
                {
                    for (int j = temp1 + 'A' + 1; j < temp2 + 'A'; ++j)
                        for (int k = 1; k <= p2; ++k)
                            putchar(j);
                }
                else
                {
                    for (int j = temp2 + 'A' - 1; j > temp1 + 'A'; --j)
                        for (int k = 1; k <= p2; ++k)
                            putchar(j);
                }
            }
            else
            {
                for (int j = temp2 - 1; j > temp1; --j)
                    for (int k = 1; k <= p2; ++k)
                        putchar('*');
            }
            continue;
        }
        putchar(all[i]);
    }
    return 0;
}