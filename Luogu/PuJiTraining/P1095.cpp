#include <cstdio>
using namespace std;
int m,s,t;
int s1,s2;
int main()
{
    scanf("%d%d%d",&m,&s,&t);
    for(int i = 1;i<=t;++i)
    {
        s1 += 17;
        if(m >= 10)
            s2 += 60,m -= 10,s1=(s2>s1?s2:s1);
        else
            m += 4;
        if(s1 >= s)
        {
            printf("Yes\n%d",i);
            return 0;
        }
    }
    printf("No\n%d",s1);
    return 0;
}