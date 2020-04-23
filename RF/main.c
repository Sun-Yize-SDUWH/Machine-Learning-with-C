// 18数据科学 孙易泽
// 学号：201800820135
// Random Forest算法

// 命令行中，如下命令编译和运行
// gcc -o main main.c RF.c
// ./main

#include <stdio.h>

// 计算出样本每个变量中，有几个分类，以及每个分类名称，储存在结构体中
void featurenum(char **matrix, int num, int col);
// 计数函数，计算输入数组，每种分类的个数
void countnum(char *array, char *compare, int num, int classnum);
// 计算基尼指数
float *gini(char **matrix, int num, int colfe, int col);
// 决策树函数，采用CART算法
void decisionTree(char **matrix, char *sample, int num, int col);
// 随机森林，进行多次随机有放回抽取样本，并把样本提供给决策树
char randomForest(char **matrix, char *sample, int num, int col, int treenum);


// 主函数，读取文件，划分训练集和测试集，并最终输出结果
int main()
{
    printf("随机森林程序运行中...\n");

    /********************
    以下几行为可修改的参数
    ********************/
    // 输入样本文件名
    char filename[] = "./mushroom.txt";
    // 输入样本数量
    int num = 8124;
    // 选取样本中最后多少行数据作为测试集
    int samplenum = 100;
    // 输入样本维度
    int col = 23;
    // 输入一共生成多少颗树
    int treenum = 6;


    // 定义样本集中正确的次数
    float correct = 0;
    // 自变量的维度
    int col_x = col - 1;
    // 训练集数目
    int num_x = num - samplenum;
    // 从文件中读取所需整体样本数据
    char data[num][col];
    FILE *fp;
    fp = fopen(filename, "r");
    for (int t = 0; t < num; t++)
        for (int i = 0; i < col; i++)
            fscanf(fp, "%[^,^\n]%*c", &data[t][i]);
    fclose(fp);

    // 处理数据，将对应矩阵作为参数进行传递
    char *p1[sizeof(data) / sizeof(data[0])];
    for (int i1 = 0; i1 < sizeof(data) / sizeof(data[0]); i1++)
        p1[i1] = data[i1];

    // 逐个输入测试集合
    for (int i1 = 0; i1 < samplenum; i1++)
    {
        // 生成测试样本
        char sample[col];
        for (int i2 = 0; i2 < col; i2++)
            sample[i2] = p1[num - i1 - 1][i2];

        // 输入随机森林函数，输入值分别为：训练样本，测试样本，训练样本数目，自变量维度，森林中树木数量
        char p = randomForest(p1, sample, num_x, col_x, treenum);
        // 如结果正确，正确数+1
        if (p==sample[col-1])
            correct++;
    }

    // 打印出测试集正确率以及其他数据
    printf("样本集为%s\n共训练%d个样本，选取%d个作为测试集，森林包含%d棵树\n其中，测试集的正确率为%.1f%%。\n", filename, num_x, samplenum, treenum, correct / (float)samplenum * 100);
}
