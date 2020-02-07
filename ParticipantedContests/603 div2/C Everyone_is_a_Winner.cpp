#include <cstdio>
#include <set>
#include <cmath>
using namespace std;
int t, n;
set<int> out;
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        out.clear();
        scanf("%d", &n);
        out.insert(0);
        int lim = sqrt(n);
        for (int i = 1; i <= lim; ++i)
        {
            out.insert(i);
            out.insert(n / i);
        }
        printf("%d\n",out.size());
        for (set<int>::iterator it = out.begin(); it != out.end(); ++it)
            printf("%d ", *it);
        printf("\n");
    }
    return 0;
}