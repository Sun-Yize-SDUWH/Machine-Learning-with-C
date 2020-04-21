// 18数据科学 孙易泽
// 学号：201800820135
// Regression Tree算法

// 命令行中，如下命令编译和运行
// gcc -o main main.c RT.c
// ./main

#include <stdio.h>

// 声明回归树函数
extern float* minmax(float **matrix,int num,int col);
extern float *regressionTree(float **matrix, int num, int col);
extern void treeformat(float **matrix, int num, int col, int nth, float **output, int th);
extern void treeprint(float **matrix, int num, int col, int nth);

// 主函数，生成回归树模型，将回归树从根节点开始，逐个分支打印出来
int main()
{
    // 从文件中读取所需整体样本数据
    float iris[200][4] = {0};
    FILE *fp;
    fp = fopen("./Advertising.txt", "r");
    for (int t = 0; t < 200; t++)
    {
        for (int i = 0; i < 4; i++)
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

    // Regression Tree,将参数输入，打印出对应的树模型
    // 参数分别为：整体样本存放在二重p指针，样本数为200，变量个数为3，输出的树模型为5层的回归树
    // 打印的数据为树从根节点开始的每一条分支，及其最终输出结果
    printf("\n\nR Tree:以下为数据生成的5层树模型，打印的数据为树从根节点开始的每一条分支\n可通过修改函数参数，改变生成的树层数\n\n");
    treeprint(p,200,3,5);
}
