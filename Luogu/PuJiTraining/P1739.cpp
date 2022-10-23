#include <cstdio>
using namespace std;
int left;
int main()
{
    for(char c = getchar();c!='@';c=getchar())
    {
        if(c == '(')
            ++left;
        else if(c == ')')
        {
            if(left)
                --left;
            else
            {
                printf("NO");
                return 0;
            }
        }
    }
    if(left)
        printf("NO");
    else
        printf("YES");
    return 0;
}