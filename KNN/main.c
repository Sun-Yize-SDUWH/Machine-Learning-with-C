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
    /********************
    以下几行为可修改的参数
    ********************/
    // 随机输入一个测试样本
    float test[4] = {5, 1, 6, 1};
    // 输入样本文件名
    char filename[] = "./iris.txt";
    // 输入样本数量
    int num = 150;
    // 输入样本维度
    int col = 5;
    // 输入样本结果中，一共有几种分类
    int class = 3;
    // 输入想选取的k值
    int k = 10;


    // 从文件中读取所需整体样本数据
    float data[num][col];
    FILE *fp;
    fp = fopen(filename, "r");
    for (int t = 0; t < num; t++)
        for (int i = 0; i < col; i++)
            fscanf(fp, "%f", &data[t][i]);
    fclose(fp);

    // 处理数据，将对应矩阵作为参数进行传递
    float *p1[sizeof(data) / sizeof(data[0])];
    for (int i1 = 0; i1 < sizeof(data) / sizeof(data[0]); i1++)
        p1[i1] = data[i1];


    // KNN函数，输入值分别为：整体样本，要判断的输入，k值，样本总体数量，样本特征数，总共有几类
    int nth;
    nth = KNN(p1, test, k, num, col-1, class);
    printf("输入样本经过判断，为第%d类\n", nth);
}
