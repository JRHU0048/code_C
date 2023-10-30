
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
十大排序算法讲解：
https://blog.csdn.net/weixin_50966947/article/details/128042215?ops_request_misc=&request_id=&biz_id=102&utm_term=%E5%A4%8D%E6%9D%82%E5%BA%A6%E5%B0%8F%E4%BA%8EO%EF%BC%88n%EF%BC%89%E7%9A%84%E5%A4%A7%E6%95%B0%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~sobaiduweb~default-0-128042215.nonecase&spm=1018.2226.3001.4450


