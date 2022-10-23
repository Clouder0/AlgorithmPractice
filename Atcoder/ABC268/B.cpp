#include <cstdio>
const int maxn = 110;
char s[maxn],t[maxn];
int main()
{
    scanf("%s%s", s + 1, t + 1);
    char *p1 = s + 1, *p2 = t + 1;
    while (*p1 == *p2)
    {
        ++p1, ++p2;
        if(*p1 == '\0') 
        {
            puts("Yes");
            return 0;
        }
    }
    puts("No");
    return 0;
}