#ifndef CONFIG_H
#define CONFIG_H
#define projectPath "/Users/tanxuan21/Desktop/homework/junior-high/Programming/src/GreedySnake/"
 //默认配置对象结构体
struct settingData{
    int gameDifficult = 3;
    int foodCount = 1;
    int randSeed = 0;
    double foodGenerationPro = .5;
    double food_1_GenerationPro = .2;
    double food_2_GenerationPro = .3;
    double food_3_GenerationPro = .5;
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
