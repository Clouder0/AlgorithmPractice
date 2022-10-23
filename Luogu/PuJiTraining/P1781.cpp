#include <cstdio>
#include <cstring>
using namespace std;
const int power = 1000000000;
struct hp
{
    int num[13];
    hp()
    {
        memset(num,0,sizeof(num));
    }
    hp(char *s) : hp()
    {
        int n = strlen(s);
        int j = 1,k = 1;
        for(int i = 1;i<=n;++i)
        {
            if(k == power)
                k = 1,++j;
            num[j] += k * (s[n-i]-'0');
            k *= 10;
        }
        num[0] = j;
    }
    bool operator>(const hp &b)
    {
        if(this->num[0] != b.num[0])
            return this->num[0] > b.num[0];
        for(int i = num[0];i;--i)
            if(num[i] != b.num[i])
                return num[i] > b.num[i];
        return false;
    }
    void output()
    {
        printf("%d",num[num[0]]);
        for(int i = num[0] - 1;i;--i)
            printf("%.9d",num[i]);
    }
}all[22];
int n;
char temp[110];
int main()
{
    scanf("%d",&n);
    for(int i = 1;i<=n;++i)
    {
        scanf("%s",temp);
        all[i] = hp(temp);
    }
    int ans = 1;
    for(int i = 2;i<=n;++i)
        if(all[i] > all[ans])
            ans = i;
    printf("%d\n",ans);
    all[ans].output();
    return 0;
}