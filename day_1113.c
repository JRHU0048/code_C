#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define D 10      // 维度
#define NP 50      // 种群大小
#define G 2000     // 迭代次数

typedef struct {
    double* x;
    double fitness;
} Solution;

// 计算测试函数f8的适应度
double evaluate_f8(double* x) {
    double sum = 0.0;
    for (int i = 0; i < D; ++i) {
        sum -= x[i] * sin(sqrt(fabs(x[i])));
    }
    return sum + D * 418.98288727243369;
}

// 初始化种群
void initialize_population(Solution* population) {
    for (int i = 0; i < NP; ++i) {
        // 为每个个体分配存储空间
        population[i].x = (double*)malloc(D * sizeof(double));

        // 随机初始化个体的参数在[-500, 500]范围内
        for (int j = 0; j < D; ++j) {
            population[i].x[j] = ((double)rand() / RAND_MAX) * 1000.0 - 500.0;
        }

        // 计算个体的适应度
        population[i].fitness = evaluate_f8(population[i].x);
    }
}

// 更新算法参数（mutation factor和crossover probability）
void update_parameters(double* mu_CR, double* mu_F, double* SC_R, double* SF, double c) {
    // 更新crossover probability (CR)
    *mu_CR = (1.0 - c) * (*mu_CR) + c * (*SC_R / NP);

    // 更新mutation factor (F) 
    double mean_SF = 0.0;
    double mean_SF_squared = 0.0;

    for (int i = 0; i < NP; ++i) {
        mean_SF += SF[i];
        mean_SF_squared += SF[i] * SF[i];
    }

    *mu_F = (1.0 - c) * (*mu_F) + c * (mean_SF_squared / mean_SF);
}

// JADE算法主体
void JADE(Solution* population) {
    double mu_CR = 0.5; // 初始化参数
    double mu_F = 0.5;  // 初始化参数
    double SC_R = 0.0;
    double SF[NP];
    double c = 0.1; // 控制参数

    for (int g = 0; g < G; ++g) {
        for (int i = 0; i < NP; ++i) {
            double CRi = ((double)rand() / RAND_MAX) * 0.1 + mu_CR;
            double Fi = ((double)rand() / RAND_MAX) * 0.1 + mu_F;

            SC_R += CRi;
            SF[i] = Fi;
        }

        // 更新参数
        update_parameters(&mu_CR, &mu_F, &SC_R, SF, c);
    }
}

// 打印解决方案及其适应度
void print_solution(Solution sol) { 
    printf("适应度: %f | 解决方案：", sol.fitness);
    for (int j = 0; j < D; ++j) {
        printf("%f ", sol.x[j]);
    }
    printf("\n");
}

int main() {
    srand((unsigned)time(NULL));

    Solution* population = (Solution*)malloc(NP * sizeof(Solution));
    initialize_population(population); 

    JADE(population); 

    // 打印最终结果
    for (int i = 0; i < NP; ++i) {
        print_solution(population[i]);
        free(population[i].x);
    }

    free(population);

    system("pause");
    return 0;
}


day_1120
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define D 30      // 维度
#define NP 50      // 种群大小
#define G 2000     // 迭代次数
#define M_pi 3.141592653

typedef struct {
    double* x;
    double fitness;
} Solution;

// 计算f8适应度的计算公式
double evaluate_f8(double* x) {
    double sum = 0.0;
    for (int i = 0; i < D; ++i) {
        sum -= x[i] * sin(sqrt(fabs(x[i])));
    }
    return sum + D * 418.98288727243369;
}

// 初始化种群
void initialize_population(Solution* population) {
    for (int i = 0; i < NP; ++i) {
        // 分配存储空间
        population[i].x = (double*)malloc(D * sizeof(double));

        // 随机初始化个体的参数在[-500, 500]范围内
        for (int j = 0; j < D; ++j) {
            population[i].x[j] = ((double)rand() / RAND_MAX) * 1000.0 - 500.0;
        }

    // 计算个体的适应度
    population[i].fitness = evaluate_f8(population[i].x);
    }
}

// 更新算法参数
void update_parameters(double*u_CR, double* u_F, double* R, double* SF, double c) {
    // 更新u_CR
    *u_CR = (1.0 - c) * (*u_CR) + c * (*R / NP);

    // 更新u_F
    double mean_SF = 0.0;
    double mean_SF_squared = 0.0;

    for (int i = 0; i < NP; ++i) {
        mean_SF += SF[i];
        mean_SF_squared += SF[i] * SF[i];
    }

    *u_F = (1.0 - c) * (*u_F) + c * (mean_SF_squared / mean_SF);
}

//randc函数
double randc(double u_f) {
    double u = ((double)rand() / RAND_MAX) - 0.5;
    return u_f + 0.1 * tan(M_pi * u);
}

//randn函数
double randn(double u_cr) {
    double z = sqrt(-2.0 * log(rand() / (RAND_MAX + 1.0))) * sin(2.0 * M_pi * rand() / (RAND_MAX + 1.0));
    return u_cr + 0.1 * z;
}

// JADE算法主体
void JADE(Solution* population) {
    double u_CR = 0.5; // 初始化参数
    double u_F = 0.5;  // 初始化参数
    double R = 0.0; 
    double SF[NP];
    double c = 0.1; // 控制参数

    for (int g = 0; g < G; ++g) {
        for (int i = 0; i < NP; ++i) {
            double CRi = randn(u_CR);
            double Fi = randc(u_F);

            R += CRi;
            SF[i] = Fi;  
        }

        // 更新参数
        update_parameters(&u_CR, &u_F, &R, SF, c);
    }
}

// 打印全部解决方案及其适应度
void print_solution(Solution sol) {
    printf("适应度: %f | 解决方案：", sol.fitness);
    for (int j = 0; j < D; ++j) {
        printf("%f ", sol.x[j]); 
    }
    printf("\n");
}

//打印最小适应度以及对应的解决方案
void min_fitness_solution(Solution* solutions) {
    double min_fitness = solutions[0].fitness;  
    Solution min_fitness_solution = solutions[0];  

    for (int i = 1; i < D; ++i) {
        if (solutions[i].fitness < min_fitness) {
            min_fitness = solutions[i].fitness;
            min_fitness_solution = solutions[i];
        }
    }

    printf("适应度最小值: %f\n解决方案：", min_fitness);
    for (int j = 0; j < D; ++j) {
        printf("%f ", min_fitness_solution.x[j]);
    }
    printf("\n");
}

int main() {
    srand((unsigned)time(NULL));

    Solution* population = (Solution*)malloc(NP * sizeof(Solution));
    initialize_population(population); 

    JADE(population);

    // 打印最终结果
    /*for (int i = 0; i < NP; ++i) {
        print_solution(population[i]);
        free(population[i].x);
    }*/

    //打印最小适应度
    min_fitness_solution(population);

    free(population);

    system("pause");
    return 0; 
}
