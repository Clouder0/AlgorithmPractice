#include <cstdio>
#include <cstring>

char s[110];
int T, r1, r2, r3, r4;

char ss[10][100] = {"", "-F", "-Cl", "-Br", "-I", "-CH3", "-CH2CH3", "-CH2CH2CH3", "-H"};

int parse(char *s)
{
    for (int i = 1; i <= 8; ++i)
        if (strcmp(s, ss[i]) == 0) return i;
    return 8;
}

int sgn(int x) { return x > 0 ? 1 : -1; }

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s", s);
        r1 = parse(s);
        scanf("%s", s);
        r2 = parse(s);
        scanf("%s", s);
        r3 = parse(s);
        scanf("%s", s);
        r4 = parse(s);
        if(r1 == r3 || r2 == r4) goto none;
        if(r1 == r2 || r3 == r4) goto cis;
        if(r1 == r4 || r2 == r3) goto trans;
        if (sgn(r1 - r3) == sgn(r2 - r4)) goto zasa;
        goto en;
    none:
        puts("None");
        continue;
    cis:
        puts("Cis");
        continue;
    trans:
        puts("Trans");
        continue;
    zasa:
        puts("Zasamman");
        continue;
    en:
        puts("Entgegen");
        continue;
    }
    return 0;
}