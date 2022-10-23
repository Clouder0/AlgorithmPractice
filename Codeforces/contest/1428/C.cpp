#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 2e5 + 100;
int T;
char s[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",s + 1);
        int n = strlen(s + 1),res = n;
        int anum = 0,bnum = 0;
        for (int i = 1; i <= n; ++i) 
        {
            if(s[i] == 'A') ++anum;
            else 
            {
                if (anum) --anum, res -= 2;
                else ++bnum;
            }
        }
        res -= (bnum & (~1));
        printf("%d\n", res);
    }
    return 0;
}