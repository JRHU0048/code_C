#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_PARTICLES 30   // 粒子数量
#define N_DIMENSIONS 2   // 维度
#define MAX_ITERATIONS 100  // 最大迭代次数
#define C1 2.0  // 学习因子1
#define C2 2.0  // 学习因子2
#define INERTIA_WEIGHT 0.5  // 惯性权重
#define PHI 0.5  // 参数 ϕ

// 定义粒子结构体
typedef struct {
    double position[N_DIMENSIONS];  // 粒子位置
    double velocity[N_DIMENSIONS];  // 粒子速度
    double personal_best[N_DIMENSIONS];  // 个体最佳位置
    double fitness;  // 适应度值
} Particle;

// 定义全局最佳位置和适应度值
double global_best[N_DIMENSIONS];
double global_best_fitness;

// 计算适应度函数，这里使用简单的二维 Rosenbrock 函数
//double fitness_function(double position[]) {
//    return pow((1 - position[0]), 2) + 100 * pow((position[1] - pow(position[0], 2)), 2);
//}

double fitness_function(double position[]) {
    double sum = 0.0;
    for (int i = 0; i < N_DIMENSIONS; ++i) {
        sum -= position[i] * sin(sqrt(fabs(position[i])));
    }
    return sum + N_DIMENSIONS * 418.98288727243369;
}
// 初始化粒子群
void initialize_particles(Particle particles[]) {
    for (int i = 0; i < N_PARTICLES; ++i) {
        for (int j = 0; j < N_DIMENSIONS; ++j) {
            particles[i].position[j] = (double)rand() / RAND_MAX * 1000.0 - 500.0;  // 随机初始化位置在[-500, 500]之间
            particles[i].velocity[j] = 0.0;  // 初始速度为0
            particles[i].personal_best[j] = particles[i].position[j];  // 初始个体最佳位置为当前位置
        }
        particles[i].fitness = fitness_function(particles[i].position);  // 计算初始适应度
    }
}

// 更新粒子的位置和速度
void update_particles(Particle particles[]) {
    for (int i = 0; i < N_PARTICLES; ++i) {
        // 更新速度
        for (int j = 0; j < N_DIMENSIONS; ++j) {
            double r1 = (double)rand() / RAND_MAX;
            double r2 = (double)rand() / RAND_MAX;
            double r3 = (double)rand() / RAND_MAX;

            particles[i].velocity[j] = INERTIA_WEIGHT * particles[i].velocity[j] +
                C1 * r1 * (particles[i].personal_best[j] - particles[i].position[j]) +
                C2 * r2 * (global_best[j] - particles[i].position[j]) +
                PHI * r3 * (global_best[j] - particles[i].position[j]);
        }

        // 更新位置
        for (int j = 0; j < N_DIMENSIONS; ++j) {
            particles[i].position[j] += particles[i].velocity[j];
        }

        // 更新适应度
        particles[i].fitness = fitness_function(particles[i].position);

        // 更新个体最佳位置
        if (particles[i].fitness < fitness_function(particles[i].personal_best)) {
            for (int j = 0; j < N_DIMENSIONS; ++j) {
                particles[i].personal_best[j] = particles[i].position[j];
            }
        }

        // 更新全局最佳位置
        if (particles[i].fitness < global_best_fitness) {
            global_best_fitness = particles[i].fitness;
            for (int j = 0; j < N_DIMENSIONS; ++j) {
                global_best[j] = particles[i].position[j];
            }
        }
    }
}

// 主循环
void bee_swarm_optimization(Particle particles[]) {
    int t = 0;

    while (t < MAX_ITERATIONS) {
        // 更新粒子位置和速度
        update_particles(particles);

        // 打印当前迭代的全局最佳适应度值
        printf("迭代次数 %d: 全局最佳适应度= %f\n", t + 1, global_best_fitness);

        t++;
    }
}

int main() {
    Particle particles[N_PARTICLES];

    // 初始化粒子群
    initialize_particles(particles);

    // 初始化全局最佳位置
    global_best_fitness = fitness_function(particles[0].position);
    for (int j = 0; j < N_DIMENSIONS; ++j) {
        global_best[j] = particles[0].position[j];
    }

    // 调用蜂群优化主循环
    bee_swarm_optimization(particles);

    // 打印最终结果
    printf("\n最优解:\n");
    printf("全局最佳适应度 = %f\n", global_best_fitness);
    printf("全局最佳位置= (%f, %f)\n", global_best[0], global_best[1]);

    system("pause");
    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define D 30  // 维度
#define NP 100   //种群规模
#define G 2000   //迭代次数

// f8
double evaluate_f8(double* x) {
    double sum = 0.0;
    for (int i = 0; i < D; ++i) {
        sum -= x[i] * sin(sqrt(fabs(x[i])));
    }
    return sum + D * 418.98288727243369;
}

// 随机生成[0, 1]之间的随机数
double random_double() {
    return rand() / ((double)RAND_MAX + 1);
}

// 竞争性种群优化器主要函数
void competitive_swarm_optimizer() {
    // 初始化粒子群
    double particles[NP][D];
    double velocities[NP][D];

    // 记录每一代的最优解和全局最优位置
    double best_solutions[G];  // 假设最大迭代次数为2000
    double global_best_position[D];
    double global_best_fitness = INFINITY;

    // 初始化其他参数
    int t = 0;
    int U[NP];
    for (int i = 0; i < NP; ++i) {
        U[i] = i;
    }

    while (t < G) {  // 最大适应度评估次数
        // 计算适应度
        double fitness_values[NP];
        for (int i = 0; i < NP; ++i) {
            fitness_values[i] = evaluate_f8(particles[i]);
        }

        // 更新全局最优位置
        for (int i = 0; i < NP; ++i) {
            if (fitness_values[i] < global_best_fitness) {
                global_best_fitness = fitness_values[i];
                for (int j = 0; j < D; ++j) {
                    global_best_position[j] = particles[i][j];
                }
            }
        }

        // 记录每一代的最优解
        best_solutions[t] = global_best_fitness;

        // 选择两个粒子进行竞争
        int idx1 = rand() % NP;
        int idx2;
        do {
            idx2 = rand() % NP;
        } while (idx2 == idx1);

        // 确定竞争结果
        int winner, loser;
        if (fitness_values[idx1] <= fitness_values[idx2]) {
            winner = idx1;
            loser = idx2;
        }
        else {
            winner = idx2;
            loser = idx1;
        }

        // 更新获胜粒子
        for (int i = 0; i < D; ++i) {
            particles[loser][i] = particles[winner][i];
        }

        // 使用学习策略更新失败粒子的速度
        double R1[D], R2[D], R3[D];
        for (int i = 0; i < D; ++i) {
            R1[i] = random_double();
            R2[i] = random_double();
            R3[i] = random_double();
        }

        double phi = 0.5;  // 调整X¯(t)影响的参数

        // 计算全局平均位置
        double global_average[D] = { 0 };
        for (int i = 0; i < NP; ++i) {
            for (int j = 0; j < D; ++j) {
                global_average[j] += particles[i][j];
            }
        }
        for (int i = 0; i < D; ++i) {
            global_average[i] /= NP;
        }

        // 计算局部平均位置
        double local_average[D] = { 0 };
        for (int i = 0; i < NP-1; ++i) {
            for (int j = 0; j < D; ++j) {
                local_average[j] += particles[U[i]][j];
            }
        }
        for (int i = 0; i < D; ++i) {
            local_average[i] /= NP-1;
        }

        // 更新失败粒子的速度
        for (int i = 0; i < D; ++i) {
            velocities[loser][i] = R1[i] * velocities[loser][i] + R2[i] * (particles[winner][i] - particles[loser][i])
                + phi * R3[i] * (global_average[i] - particles[loser][i])
                + (1 - phi) * R3[i] * (local_average[i] - particles[loser][i]);
        }

        // 更新失败粒子的位置
        for (int i = 0; i < D; ++i) {
            particles[loser][i] += velocities[loser][i];
        }

        // 更新U，将参与竞争的粒子移除
        for (int i = 0; i < NP; ++i) {
            if (U[i] == idx1 || U[i] == idx2) {
                U[i] = -1;
            }
        }
        int count = 0;
        for (int i = 0; i < NP; ++i) {
            if (U[i] != -1) {
                U[count] = U[i];
                count++;
            }
        }
        // 将更新后的粒子加入下一代粒子群
        t++;
    }

    // 输出每一代的最优解和全局最优位置
    for (int i = 0; i < G; ++i) {
        printf("第 %d 代的最优解：%lf\n", i + 1, best_solutions[i]);
    }

    printf("全局最优位置：[");
    for (int i = 0; i < D - 1; ++i) {
        printf("%lf, ", global_best_position[i]);
    }
    printf("%lf]\n", global_best_position[D - 1]);
}

int main() {
    // 运行CSO算法
    competitive_swarm_optimizer();

    system("pause");
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////


day1211
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NP 100        // 种群规模
#define D 30          // 维度
#define G 2000        //迭代次数
#define FI 0.5       //// 参数 ϕ

double calculate_fitness(double position[]) {    //个体的计算适应度值
    double sum = 0.0;
    for (int i = 0; i < D; ++i) {
        sum += position[i] * sin(sqrt(fabs(position[i])));
    }
    return  D * 418.98288727243369-sum;
}

double random_double() {    //生成0、1之间的随机数
    return rand() / ((double)RAND_MAX + 1);
}

void initialize_aveparticles(double aveparticles[], double particles[][D]) {  //计算种群平均位置数组
    for (int i = 0;i < D;++i)  //初始化aveparticles
    {
        aveparticles[i] = 0;
    }
    for (int j = 0;j < D;++j)  //在 C 中，在函数中声明二维数组参数时，必须指定至少一个维度的大小。在本例中， D 是第二个维度的大小（列数）。
    {
        for (int i = 0;i < NP;++i)
        {
            aveparticles[j] += particles[i][j];
        }
        aveparticles[j]  /=  NP;  //浮点数
    }
}

int main() {
    // 定义粒子群
    double particles[NP][D];    //存储粒子位置信息
    double velocities[NP][D];   //存储粒子速度信息
    double aveparticles[D];     //存储平均位置信息
    double best_fitness[G];       // 假设最大迭代次数为G,用来存储每一代的最佳适应度
    double global_best_fitness = INFINITY;    //全局最佳适应度，初始化为正无穷大，可以确保在开始时，任何一个粒子的适应度值都能够成为当前的最佳适应度值。
    double global_best_position[D];  //全局最优解的位置

    srand((unsigned int)time(NULL));

    // 初始化其他参数
    int t = 0;
    int U[NP];   //初始化尚未参加比赛的粒子集
    for (int i = 0; i < NP; ++i) {
        U[i] = i;   //未参与过的赋值i
    }
   
    for (int i = 0;i < NP;++i)     //初始化位置信息
    {
        for (int j = 0;j < D;++j)
        {
            particles[i][j] = rand() % 1001 - 500;   //位置为 -500到500之间
        }
    }

    for (int i = 0;i < NP;++i)   //初始化速度信息
    {
        for (int j = 0;j < D;++j)
        {
            velocities[i][j] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;  //随机初始化速度为 -1.0到1.0之间
        }
    }

    initialize_aveparticles(aveparticles, particles); //计算种群平均位置数组
    
    while (t < G) {  // 最大迭代次数
        // 计算适应度
        double fitness_values[NP];   //计算同一代中所有个体的适应度
        for (int i = 0; i < NP; ++i) {
            fitness_values[i] = calculate_fitness(particles[i]);  //particles[i]表示调用第i行，是一个一维数组
        }

        // 更新全局最优解以及最优位置
        for (int i = 0; i < NP; ++i) {
            if (fitness_values[i] < global_best_fitness) {
                global_best_fitness = fitness_values[i];    //更新适应度为较小的值
                for (int j = 0; j < D; ++j) {
                    global_best_position[j] = particles[i][j];
                }
            }
        }
        // 记录每一代的最优解
        best_fitness[t] = global_best_fitness;

        // 选择两个粒子进行竞争
        int idx1 = rand() % NP;
        int idx2 = rand() % NP;
        
        /*do {
            idx2 = rand() % NP;
        } while (idx2 != idx1);*/

        // 确定竞争结果
        int winner, loser;
        if (fitness_values[idx1] <= fitness_values[idx2]) {   //适应度较小的认为获胜
            winner = idx1;
            loser = idx2;
        }
        else {
            winner = idx2;
            loser = idx1;
        }

        // 使用学习策略更新失败粒子的速度
        double R1[D], R2[D], R3[D];
        for (int i = 0; i < D; ++i) {
            R1[i] = random_double();   //D维随机数 0-1
            R2[i] = random_double();
            R3[i] = random_double();
        }
        for (int i = 0;i < D;++i) {
            int vlt = velocities[loser][i];
            velocities[loser][i] = R1[i] * vlt + R2[i] * (particles[winner][i] - particles[loser][i]) + FI*R3[i] * (aveparticles[i] - particles[loser][i]);
            particles[loser][i] += velocities[loser][i];
        }
        // 更新U，将参与竞争的粒子移除
        for (int i = 0; i < NP; ++i) {
            if (U[i] == idx1 || U[i] == idx2) {
                U[i] = -1;    //参与过竞争的赋值-1
            }
        }
        int count = 0;
        for (int i = 0; i < NP; ++i) {
            if (U[i] != -1) {      
                U[count] = U[i];    //对于未参与过竞争的粒子放前面
                count++;
            }
        }
        //更新平均位置数组
        initialize_aveparticles(aveparticles, particles); //计算种群平均位置数组
        t++;
    }

    for (int i = 0;i < G;++i) {
        printf("种群中第%d代的最佳适应度为：%lf\n", i,best_fitness[i]);
    }
    for (int i = 0;i < D;++i)
    {
        printf("%d, ", global_best_position);
    }
    system("pause");
    return 0;
}
