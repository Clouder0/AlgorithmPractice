#include <cstdio>
using namespace std;
template <typename T>
inline int read(T &r)
{
    static char c;static int flag;flag = 1, r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar()) if (c == '-') flag = -1;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
    return r *= flag;
}
const int maxn = 100000;
int n, T;
int all[maxn];
int main()
{
    read(T);
    while (T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i)
            read(all[i]);
        int sum = 0;
        for (int i = 1; i < n; ++i)
        {
            sum += all[i];
            if (sum <= 0)
            {
                printf("What a Shame!\n");
                goto end;
            }
        }
        sum = 0;
        for (int i = n; i > 1; --i)
        {
            sum += all[i];
            if (sum <= 0)
            {
                printf("What a Shame!\n");
                goto end;
            }
        }
        printf("Just do it!\n");
    end:;
    }
    return 0;
}