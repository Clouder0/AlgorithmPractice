#include <cstdio>
#include <map>
using namespace std;
int T,n,x;
char all[1001000];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&x);
        scanf("%s",all+1);
        int val = 0;
        for(int i = 1;i<=n;++i)
        {
            if(all[i] == '0')    ++val;
            else --val;
        }
        if(val == 0 && x == 0)
        {
            printf("-1\n");
            continue;
        }
        if(x == 0 && val != 0)
        {
            int temp = 0,res = 1;
            for(int i = 1;i<=n;++i)
            {
                if(all[i] == '0')
                    ++temp;
                else
                    --temp;
                if(temp == 0)
                    ++res;
            }
            printf("%d\n",res);
            continue;
        }
        if(val > x || x / val < 0)
        {
            int temp = 0,res = 0;
            for(int i = 1;i<=n;++i)
            {
                if(all[i] == '0')
                    ++temp;
                else
                    --temp;
                if(temp == x)
                    ++res;
            }
            printf("%d\n",res);
            continue;
        }
        if(x % val == 0)
        {
            int temp = 0,res = 1;
            for(int i = 1;i<=n;++i)
            {
                if(all[i] == '0') ++temp;
                else --temp;
                if(temp == 0)
                    ++res;
            }
            temp = 0;
            for(int i = n;i;--i)
            {
                if(all[i] == '0')
                    ++temp;
                else
                    --temp;
                if(temp == 0)
                    ++res;
            }
            printf("%d\n",res);
            continue;
        }
        else
        {
            int target = x % val;
            int target2 = (x % val) + val;
            int temp = 0,res = 0;
            for(int i = 1;i<=n;++i)
            {
                if(all[i] == '0')
                    ++temp;
                else
                    --temp;
                if(temp == target || temp == target2)
                    ++res;
            }
            printf("%d\n",res);
        }
    }
    return 0;
}