#include <cstdio>
#include <cstring>
using namespace std;
char all[110];
int s[110];
char need[110];
int top,len;
int main()
{
    scanf("%s",all+1);
    len = strlen(all+1);
    for(int i = 1;i<=len;++i)
    {
        switch(all[i])
        {
            case '(':
                s[++top] = i;
                need[i] = ')';
                break;
            case ')':
                if(all[s[top]] == '(')
                    need[s[top--]] = 0;
                else
                    need[i] = '(';
                break;
            case '[':
                s[++top] = i;
                need[i] = ']';
                break;
            case ']':
                if(all[s[top]] == '[')
                    need[s[top--]] = 0;
                else
                    need[i] = '[';
                break;
        }
    }
    for(int i = 1;i<=len;++i)
    {
        if(!need[i])
        {
            putchar(all[i]);
            continue;
        }
        if(all[i] == '(' || all[i] == '[')
        {
            putchar(all[i]);
            putchar(need[i]);
            continue;
        }
        putchar(need[i]);
        putchar(all[i]);
    }
    return 0;
}