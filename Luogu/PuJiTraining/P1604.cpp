#include <cstdio>
#include <cstring>
using namespace std;
int power,al,bl;
char s1[5100],s2[5100];
int a[5100],b[5100];
void output(int i)
{
    if(i < 10)
        putchar(i + 48);
    else
        putchar(i + 55);
}
int main()
{
    scanf("%d",&power);
    scanf("%s",s1);
    al = strlen(s1);
    scanf("%s",s2);
    bl = strlen(s2);
    int len = al>bl?al:bl;
    for(int i = 0;i<al;++i)
        if(s1[i] >= 65)
            a[al-i-1] = s1[i] - 55;
        else
            a[al-i-1] = s1[i] - 48;
    for(int i = 0;i<bl;++i)
        if(s2[i] >= 65)
            b[bl-i-1] = s2[i] - 55;
        else
            b[bl-i-1] = s2[i] - 48;
    for(int i = 0;i < len;++i)
    {
        a[i] += b[i];
        if(a[i] >= power)
            a[i] -= power,++a[i+1];
    }
    if(a[len])
        ++len;
    for(int i = len-1;i>=0;--i)
        output(a[i]);
    return 0;
}