#include <cstdio>
long long t, f;
int n;
char s[40];
int main()
{
    t = f = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) 
    {
        scanf("%s",s + 1);
        if(s[1] == 'A')
        {
            long long nt = 0,nf = 0;
            //choose True
            nt += t,nf += f;
            //choose False
            nf += t + f;
            t = nt, f = nf;
        }
        else
        {
            long long nt = 0, nf = 0;
            //choose True
            nt += t + f;
            //choose False
            nt += t,nf += f;
            t = nt,f = nf;
        }
    }
    printf("%lld\n", t);
    return 0;
}