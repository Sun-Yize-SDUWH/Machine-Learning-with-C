// 18数据科学 孙易泽
// 学号：201800820135
// Simple Linear Regression算法

// 命令行中，如下命令编译和运行
// gcc -o main main.c SLR.c
// ./main

#include <stdio.h>

// 声明外部定义的Simple Linear Regression函数
extern float *regression(float **matrix, int num);

// 主函数，选取二维样本训练
int main()
{
    // 从文件中读取所需整体样本数据
    float data[30][2] = {0};
    FILE *fp;
    fp = fopen("./data.txt", "r");
    for (int t = 0; t < 30; t++)
    {
        for (int i = 0; i < 2; i++)
        {
            fscanf(fp, "%f", &data[t][i]);
        }
    }
    fclose(fp);

    // 处理数据，将对应矩阵作为参数进行传递
    float *p[sizeof(data) / sizeof(data[0])];
    for (int i1 = 0; i1 < sizeof(data) / sizeof(data[0]); i1++)
    {
        p[i1] = data[i1];
    }

    // 调用Simple Linear Regression函数
    float *result;
    result = regression(p,30);
    printf("SLR:在y=ax+b的情况下\na的值为%f\nb的值为%f\n",result[0],result[1]);
}
