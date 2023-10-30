
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float getRandomFloat(float min, float max) {
    float random = ((float) rand()) / (float) RAND_MAX;
    return min + (random * (max - min));
}
int main() {
    // 设置随机种子
    srand(time(NULL));
    // 生成随机浮点数
    float randomNum = getRandomFloat(0.0f, 1.0f);
    printf("随机浮点数: %f\n", randomNum);
    return 0;
}
