#include <cstdio>
#include <cstring>
const int maxn = 1e5 + 100;
using namespace std; 
char s[maxn];
int main()
{
    scanf("%s",s + 1);
    int n = strlen(s + 1);
    puts("3");
    printf("R %d\n",n - 1);
    printf("L %d\n",n);
    puts("L 2");
    return 0;
}