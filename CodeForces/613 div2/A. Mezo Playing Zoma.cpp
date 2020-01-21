#include <cstdio>
#include <cstring>
using namespace std;
template <typename T>
void read(T &r)
{
    static char c;r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 2e5 + 10;
char s[maxn];
int lnum, rnum;
int n;
int main()
{
    read(n);
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    for (int i = 1; i <= len; ++i)
    {
        if (s[i] == 'L')
            ++lnum;
        else
            ++rnum;
    }
    printf("%d", rnum + lnum + 1);
    return 0;
}