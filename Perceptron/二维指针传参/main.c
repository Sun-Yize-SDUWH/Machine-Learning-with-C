// 18数据科学 孙易泽
// 学号：201800820135
// 感知机perceptron算法

// 命令行中，如下命令编译和运行
// gcc -o main main.c perceptron.c
// ./main

#include <stdio.h>

// 声明外部定义的感知机函数
extern float *perceptron(float **matrix, float step, int num, int col);
float **readfile(int num, int col, char *filename);

// 读取文件，将数据存放到二维指针
float **readfile(int num, int col, char *filename)
{
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

    // 返回数组矩阵
    float **p2 = p1;
    return p2;
}

// 主函数，选取鸢尾花数据进行训练
int main()
{
    /********************
    以下几行为可修改的参数
    ********************/
    // 输入样本文件名
    char filename[] = "./iris.txt";
    // 输入样本数量
    int num = 100;
    // 输入样本维度
    int col = 3;
    // 输入步长
    float n = 0.1;


    // 打开文件，并将数据读取到二维数组中
    float **p = readfile(num, col, filename);
    // 调用perceptron算法，返回对应w和b
    float *po;
    po = perceptron(p, n, num, col-1);
}
