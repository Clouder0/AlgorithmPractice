#include <cstdio>
#include <cstring>
using namespace std;
int n,len;
char all[201];
char temp[201];
int path[201];
int tot;
bool checkblack()
{
    memcpy(temp,all,sizeof(all));
    tot = 0;
    for(int i = 1;i<len;++i)
    {
        if(temp[i] == 'W')
        {
            temp[i] = 'B';
            temp[i+1] = (temp[i+1] == 'W' ? 'B' : 'W');
            path[++tot] = i;
        }
    }
    return temp[len] == 'B';
}
bool checkwhite()
{
    memcpy(temp,all,sizeof(all));
    tot = 0;
    for(int i = 1;i<len;++i)
    {
        if(temp[i] == 'B')
        {
            temp[i] = 'W';
            temp[i+1] = (temp[i+1] == 'W' ? 'B' : 'W');
            path[++tot] = i;
        }
    }
    return temp[len] == 'W';
}
int main()
{
    scanf("%d",&n);
    scanf("%s",all+1);
    len = strlen(all+1);
    if(checkblack() || checkwhite())
    {
        printf("%d\n",tot);
        for(int i =1 ;i<=tot;++i)
            printf("%d ",path[i]);
    }
    else
        printf("-1");
    return 0;
}