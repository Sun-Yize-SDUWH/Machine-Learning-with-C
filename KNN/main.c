// 18数据科学 孙易泽
// 学号：201800820135
// k-Nearest Neighbors算法

// 命令行中，如下命令编译和运行
// gcc -o main main.c KNN.c
// ./main

#include <stdio.h>

// 声明外部定义的KNN函数
extern int KNN(float **matrix, float *inputs, int k, int num, int col, int class);

// 主函数，选取鸢尾花数据进行分类测试
int main()
{
    // 从文件中读取所需整体样本数据
    float iris[150][5] = {0};
    FILE *fp;
    fp = fopen("./iris.txt", "r");
    for (int t = 0; t < 150; t++)
    {
        for (int i = 0; i < 5; i++)
        {
            fscanf(fp, "%f", &iris[t][i]);
        }
    }
    fclose(fp);

    // 处理数据，将对应矩阵作为参数进行传递
    float *p[sizeof(iris) / sizeof(iris[0])];
    for (int i1 = 0; i1 < sizeof(iris) / sizeof(iris[0]); i1++)
    {
        p[i1] = iris[i1];
    }

    // 测试样本参数，输入KNN算法判断具体属于哪一类
    float test[4] = {5, 1, 6, 1};

    // KNN函数，输入值分别为：整体样本，要判断的输入，k值，样本总体数量，样本特征数，总共有几类
    int nth;
    nth = KNN(p, test, 10, 150, 4, 3);
    printf("输入样本经过判断，为第%d类\n", nth);
}