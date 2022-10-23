#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int maxn = 20;
int a[maxn];
int main()
{
    while(scanf("%d %d %d %d %d %d %d %d %d %d",a + 1,a + 2,a +3,a+4,a+5,a+6,a+7,a+8,a+9,a+10) != EOF)
    {
        int start = 2;
        int final = 6;
        for(int i = 1;i<=10;++i)
        {
            if(a[i] == 1) ++start;
            else if(a[i] == 0) continue;
            else if(a[i] == 7) --start;
            if(start < 0) start = 0;
            else if(start > final) start = final;
        }
        if(start == final) puts("666");
        else puts("777");
    }
    return 0;
}