#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
int P;
const unsigned long long power = 100000;
struct hp
{
    unsigned long long num[101];
    hp()
    {
        memset(num, 0, sizeof(num));
    }
    hp operator=(const hp &b)
    {
        memcpy(this->num, b.num, sizeof(b.num));
    }
    hp operator*(const hp &b)
    {
        hp r;
        r.num[0] = this->num[0] + b.num[0] + 1;
        if (r.num[0] > 100)
            r.num[0] = 100;
        for (int i = 1; i <= num[0]; ++i)
            for (int j = 1; j <= b.num[0]; ++j)
                if (i + j <= 101)
                {
                    r.num[i + j - 1] += num[i] * b.num[j];
                    r.num[i + j] += r.num[i + j - 1] / power;
                    r.num[i + j - 1] %= power;
                }
        while (r.num[r.num[0]] == 0 && r.num[0] > 1)
            --r.num[0];
        return r;
    }
    void output()
    {
        for (int i = 10; i; --i)
        {
            for (int j = 0; j < 10; ++j)
                printf("%.5d", num[10 * i - j]);
            putchar('\n');
        }
    }
};
void fastpow()
{
    hp ans, t;
    ans.num[0] = ans.num[1] = 1;
    t.num[0] = 1;
    t.num[1] = 2;
    while (P)
    {
        if (P & 1)
            ans = ans * t;
        t = t * t;
        P >>= 1;
    }
    --ans.num[1];
    ans.output();
}
int main()
{
    scanf("%d", &P);
    printf("%d\n", (int)(log10(2) * (double)P) + 1);
    fastpow();
    return 0;
}