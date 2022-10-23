#include <cstdio>
#include <algorithm>
int a, b, c;

int main() {
    scanf("%d%d%d", &a, &b, &c);
    if(a == 1 && b == 0 && c == 0) 
        printf("YES\n0\n");
    else if(a > b + c) 
        printf("YES\n%d\n", 2 * (b + c) + 1);
    else 
        printf("NO\n");
    return 0;
}