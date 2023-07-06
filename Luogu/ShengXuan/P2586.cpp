#include <cstdio>
#include <list>
#include <cmath>

int n, m, s, t, d, r;
int cakeCarried;

struct tower
{
    int x, y;
} Towers[30];

struct ant
{
    int x, y;
    int maxHP, HP;
    int hasCake;
    int age;
};

std::list<ant> ants;
int totalAnts;

void generateAnt()
{
    if (ants.size() >= 6) return;
    for (auto v : ants)
        if (v.x == 0 && v.y == 0) return;  // can't generate ant when (0,0) is occupied
    // now generate new ant
    ++totalAnts;
    int level = (totalAnts + 5) / 6;
    int levelHP = 4 * std::pow(1.1, level);
    ants.push_back((ant){0, 0, levelHP, levelHP, 0, 0});
}

int infoC[10][10];

void refuceInfo()
{
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            if (infoC[i][j] > 0) --infoC[i][j];
}

void generateInfo()
{
    for (auto v : ants) infoC[v.x][v.y] += (v.hasCake ? 5 : 2);
}

void ageAnts()
{
    for (auto& v : ants) ++v.age;
}

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool checkPoint(int nx, int ny)
{
    if (nx < 0 || ny < 0 || nx > n || ny > m) return false;
    for (auto v : ants)
        if (nx == v.x && ny == v.y) return false;
    for (int i = 1; i <= s; ++i)
        if (nx == Towers[i].x && ny == Towers[i].y) return false;
    return true;
}

void moveAnts()
{

}

void getCake()
{

}

void attack()
{

}

void runSecond() {
    generateAnt();
    generateInfo();
    moveAnts();
    getCake();
    attack();
    refuceInfo();
    ageAnts();
}

int main()
{
    scanf("%d%d", &n, &m);
    scanf("%d%d%d", &s, &d, &r);
    for (int i = 1; i <= s; ++i) scanf("%d%d", &Towers[i].x, &Towers[i].y);
    return 0;
}