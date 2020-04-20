// 18数据科学 孙易泽
// 学号：201800820135
// 感知机perceptron算法

// 命令行中，如下命令编译和运行
// gcc -o main main.c perceptron.c
// ./main

#include <stdio.h>

// 声明外部定义的感知机函数
float *perceptron(float **matrix, float step, int num, int col);

// 主函数，选取鸢尾花数据进行训练
int main()
{
    // 从文件中读取训练所需数据
    float flower[100][3] = {0};
    FILE *fp;
    fp = fopen("./iris.txt", "r");
    for (int t = 0; t < 100; t++)
    {
        for (int i = 0; i < 3; i++)
        {
            fscanf(fp, "%e", &flower[t][i]);
        }
    }
    fclose(fp);

    // 处理数据，将对应矩阵作为参数进行传递
    float *p[sizeof(flower) / sizeof(flower[0])];
    for (int i1 = 0; i1 < sizeof(flower) / sizeof(flower[0]); i1++)
    {
        p[i1] = flower[i1];
    }

    // 调用perceptron算法，返回对应w和b
    float *p1;
    p1 = perceptron(p, 0.1, 100, 2);
}
