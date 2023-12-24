#ifndef CONFIG_H
#define CONFIG_H
#define projectPath "D:/snake/gg2/GreedySnake/"
 //默认配置对象结构体
struct settingData{
    int gameDifficult = 3;
    int foodCount = 1;
    int randSeed = 0;
    double foodGenerationPro1 = .5;
    double food_1_GenerationPro = .6;
    double food_2_GenerationPro = .3;
    double food_3_GenerationPro = .1;
    int mapWidth = 10;
    int mapHeight = 10;

    int upwall = true;
    int downwall = true;
    int leftwall = true;
    int rightwall = true;

    int blockContinuous = 1;
    int blockCount = 0;

};
#endif // CONFIG_H
