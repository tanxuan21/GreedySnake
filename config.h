#ifndef CONFIG_H
#define CONFIG_H
#define projectPath "/Users/tanxuan21/Desktop/homework/junior-high/Programming/GreedySnake/"
 //默认配置对象结构体
struct settingData{
    int gameDifficult = 1;
    int foodCount = 1;
    int randSeed = 0;
    double foodGenerationPro = .5;

    int mapWidth = 10;
    int mapHeight = 10;

    int upwall = false;
    int downwall = false;
    int leftwall = false;
    int rightwall = false;

    int blockContinuous = 1;
    int blockCount = 0;
};
#endif // CONFIG_H
