#include <algorithm>
#include <cstdio>
#include <cstring>
const int maxn = 1000;
int T, al, bl;
char A[maxn], B[maxn], C[maxn];
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", A + 1), scanf("%s", B + 1);
        al = strlen(A + 1), bl = strlen(B + 1);
        for (int i = 1; i <= al; ++i) A[i] -= '0';
        for (int i = 1; i <= bl; ++i) B[i] -= '0';
        while (A[al] == 0 && al > 1) --al;
        while (B[bl] == 0 && bl > 1) --bl;
        // std::reverse(A + 1,A +1 + al);
        // std::reverse(B + 1,B +1 + bl);
        int newl = std::max(al,bl);
        for (int i = 1; i <= newl; ++i) 
        {
            A[i] += B[i];
            if(A[i] >= 10) ++A[i+1],A[i] -= 10;
        }
        if (A[newl + 1] > 0) ++newl;
        std::reverse(A + 1,A + 1 + newl);
        while(A[newl] == 0 && newl > 1) --newl;
        A[newl + 1] = '\0';
        for(int i = newl;i;--i) putchar('0' + A[i]);
        puts("");
    }
    return 0;
}