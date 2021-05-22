#include "GameMain.h"

static int rowCount = 10;

int main()
{
    int** world = new int*[rowCount];
    for(int i = 0; i < rowCount; ++i)
    {
        world[i] = new int[rowCount];
    }
    GameMain gm;
    gm.mainGameLoop();

    return 0;
}
