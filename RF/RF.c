/*******************
Random Forest函数代码
*******************/
#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
#include <time.h>
#define FLT_MAX 3.402823466e+38F

// 定义决策树输出分类结果，全局变量
char decisionTreeOutput;

// 变量特征的结构体，储存每个变量有几个分类，以及每个分类名称
struct Class1
{
    int feturenum;
    char feturename[20];
    int flag;
} feture[] = {0};

// 计数结构体，计算每个种类的个数
struct Class2
{
    char classname;
    int classnum;
} class[] = {0};


// 计数函数，计算输入数组，每种分类的个数
void countnum(char *array, char *compare, int num, int classnum)
{
    // 初始化结构体
    for (int i1 = 0; i1 < classnum; i1++)
    {
        class[i1].classname = compare[i1];
        class[i1].classnum = 0;
    }
    // 对所有样本遍历
    for (int i2 = 0; i2 < num; i2++)
    {
        for (int i3 = 0; i3 < classnum; i3++)
        {
            // 样本所属的对应类别+1
            if (array[i2] == class[i3].classname)
            {
                class[i3].classnum++;
                break;
            }
        }
    }
}

// 计算出样本每个变量中，有几个分类，以及每个分类名称，储存在结构体中
void featurenum(char **matrix, int num, int col)
{
    // 标志变量
    int flag1 = 0;
    // 转换为总体样本维度（加上最后结果的一维）
    col++;

    // 初始化特征的结构体
    for (int temp1 = 0; temp1 < col; temp1++)
    {
        feture[temp1].feturenum = 1;
        feture[temp1].feturename[0] = matrix[0][temp1];
        feture[temp1].flag = 0;
    }

    // 逐个特征进行遍历
    for (int i1 = 0; i1 < col; i1++)
    {
        // 逐个样本遍历
        for (int i2 = 0; i2 < num; i2++)
        {
            // 标志变量归0
            flag1 = 0;
            for (int i3 = 0; i3 < feture[i1].feturenum; i3++)
            {
                if (feture[i1].feturename[i3] == matrix[i2][i1])
                {
                    flag1 = 1;
                    break;
                }
            }
            // 如在已知类别中无匹配，则添加到新类别
            if (flag1 == 0)
            {
                feture[i1].feturename[feture[i1].feturenum] = matrix[i2][i1];
                feture[i1].feturenum++;
            }
        }
    }
}

// 计算基尼指数，返回值为对应特征最小基尼系数，及其对应的最优的切分点
float *gini(char **matrix, int num, int colfe, int col)
{
    // 定义返回值数组，分别为：特征最小基尼系数，对应特征，对应的最优的切分点
    static float output[3];
    // 计数变量
    int count1, count2;
    // 临时变量，储存计算数据
    float temp;
    // 基尼系数临时储存变量
    float gini1, gini2, ginisum;
    // 当前最小基尼系数，初始值设定一较大值
    float ginimin = FLT_MAX;
    // 将二维数组转换为对应特征的一位数组，传入计数变量
    char array1[num], array2[num];

    // 对应特征的逐个分类进行遍历
    for (int i1 = 0; i1 < feture[colfe].feturenum; i1++)
    {
        count1 = 0, count2 = 0, temp = 0;
        for (int i2 = 0; i2 < num; i2++)
        {
            // 根据对应切分点，分为两类：属于该切分点和不属于的
            if (matrix[i2][colfe] == feture[colfe].feturename[i1])
            {
                array1[count1] = matrix[i2][col];
                count1++;
            }
            else
            {
                array2[count2] = matrix[i2][col];
                count2++;
            }
        }

        // 计算第一类的数量
        countnum(array1, feture[col].feturename, count1, feture[col].feturenum);
        for (int i3 = 0; i3 < feture[col].feturenum; i3++)
            temp += ((float)class[i3].classnum / (float)count1) * ((float)class[i3].classnum / (float)count1);
        temp = (float)1 - temp;
        // 算出第一类的基尼系数，并乘以对应比重
        gini1 = ((float)count1 / (float)num) * temp;

        // 临时变量归0
        temp = 0;
        // 计算第二类的数量
        countnum(array2, feture[col].feturename, count2, feture[col].feturenum);
        for (int i4 = 0; i4 < feture[col].feturenum; i4++)
            temp += ((float)class[i4].classnum / (float)count2) * ((float)class[i4].classnum / (float)count2);
        temp = 1 - temp;
        // 算出第二类的基尼系数，并乘以对应比重
        gini2 = ((float)count2 / (float)num) * temp;
        // 两类基尼系数相加，算出特征下对应切分点的基尼系数
        ginisum = gini1 + gini2;

        // 如果是目前最小的基尼系数，则储存值和对应切分点
        if (ginisum < ginimin)
        {
            ginimin = ginisum;
            output[0] = ginisum;
            output[1] = (float)colfe;
            output[2] = (float)i1;
        }
    }

    // 返回最终计算最小基尼系数，对应特征，对应的最优的切分点
    float *p = output;
    return p;
}

// 决策树函数，采用CART算法
void decisionTree(char **matrix, char *sample, int num, int col)
{
    // 标志变量
    int flag1 = 1, flag2 = 0;
    // 指针变量，储存gini函数的返回值
    float *tempgini;
    // 特征的最小基尼系数，初始值为一较大值
    float ginimin = FLT_MAX;
    // j为最优特征，s为最优特征的最优切分点
    int j, s;
    // 计数变量
    int count1 = 0, count2 = 0;
    // 储存经过js分类后的训练样本
    char leaf[num][col + 1];
    // 最终输出结果
    char output;
    // 输入计数函数的数组
    char array[num];

    // 查看是否仍存在未分类的特征
    for (int i1 = 0; i1 < col - 1; i1++)
    {
        if (feture[i1].flag == 0)
        {
            flag1 = 0;
            break;
        }
    }
    // 查看输入样本是否都属于同一类
    for (int i2 = 0; i2 < num; i2++)
        array[i2] = matrix[i2][col];
    countnum(array, feture[col].feturename, num, feture[col].feturenum);
    // 查看样本是否属于同一类
    for (int i3 = 0; i3 < feture[col].feturenum; i3++)
    {
        if (class[i3].classnum == num)
        {
            flag1 = 1;
            break;
        }
    }

    // 如果样本属于同一类或所有特征均已被分类，则输出结果
    // 如果没有，则继续进行决策树递归
    if (flag1 == 1 || flag2 == 1)
        decisionTreeOutput = matrix[0][col];
    else
    {
        // 对没有进行分类的特征，逐个计算基尼系数，算出最优特征
        for (int temp1 = 0; temp1 < col; temp1++)
        {
            if (feture[temp1].flag == 0)
            {
                // 放入基尼系数计算函数进行计算
                tempgini = gini(matrix, num, temp1, col);
                // 如果为当前最小基尼系数，则储存对应特征和特征对应切分点
                if (tempgini[0] < ginimin)
                {
                    ginimin = tempgini[0];
                    j = temp1;
                    s = (int)tempgini[2];
                }
            }
        }
        // 对应特征被标记为1，代表已进行过分类
        feture[j].flag = 1;
        // 根据切分点，将原有样本分类形成子样本，进行决策树递归
        // 选择和测试集相符的分支进行分类
        if (sample[j] == feture[j].feturename[s])
        {
            // 逐个样本遍历
            for (int temp2 = 0; temp2 < num; temp2++)
            {
                if (matrix[temp2][j] == feture[j].feturename[s])
                {
                    // 对应子样本进行储存
                    for (int temp3 = 0; temp3 < col + 1; temp3++)
                        leaf[count1][temp3] = matrix[temp2][temp3];
                    count1++;
                }
            }
            // 处理子样本
            char *p1[sizeof(leaf) / sizeof(leaf[0])];
            for (int i1 = 0; i1 < sizeof(leaf) / sizeof(leaf[0]); i1++)
                p1[i1] = leaf[i1];
            // 子样本放入决策树，开始递归
            decisionTree(p1, sample, count1, col);
        }
        else
        {
            // 逐个样本遍历
            for (int temp3 = 0; temp3 < num; temp3++)
            {
                if (matrix[temp3][j] != feture[j].feturename[s])
                {
                    // 对应子样本进行储存
                    for (int temp4 = 0; temp4 < col + 1; temp4++)
                        leaf[count2][temp4] = matrix[temp3][temp4];
                    count2++;
                }
            }
            // 处理子样本
            char *p2[sizeof(leaf) / sizeof(leaf[0])];
            for (int i1 = 0; i1 < sizeof(leaf) / sizeof(leaf[0]); i1++)
                p2[i1] = leaf[i1];
            // 子样本放入决策树，开始递归
            decisionTree(p2, sample, count2, col);
        }
    }
}

// 随机森林，进行多次随机有放回抽取样本，并把样本提供给决策树
char randomForest(char **matrix, char *sample, int num, int col, int treenum)
{
    // 储存有放回抽取的随机样本
    char random[num][col + 1];
    // 储存所有决策树返回的结果
    char outputs[treenum];
    // 有放回随机数的生成
    int randomnum;
    // 储存最多的投票数，计数变量
    int classmax = 0, count = 0;
    // 最多投票数对应的类别名称
    char classname;

    // 放入特征函数，计算出样本每个变量中，有几个分类，以及每个分类名称，储存在结构体中
    featurenum(matrix, num, col);
    // 按照设定树的数量，逐个树进行计算
    for (int temp1 = 0; temp1 < treenum; temp1++)
    {
        count = 0;
        // 随机有放回抽取样本，并将样本储存
        for (int i1 = 0; i1 < num; i1++)
        {
            srand(i1 * time(NULL));
            randomnum = rand() % (num - 2);
            for (int i2 = 0; i2 < col + 1; i2++)
                random[count][i2] = matrix[randomnum][i2];
            count++;
        }
        // 处理抽取好的样本
        char *p[sizeof(random) / sizeof(random[0])];
        for (int i3 = 0; i3 < sizeof(random) / sizeof(random[0]); i3++)
            p[i3] = random[i3];

        // 放入决策树，开始计算
        decisionTree(p, sample, count, col);
        // 返回结果储存在公共变量，提出到结果数组中
        outputs[temp1] = decisionTreeOutput;
    }
    // 计算所有树中，返回的每种结果的数量
    countnum(outputs, feture[col].feturename, treenum, feture[col].feturenum);
    // 选取投票结果最多的类别
    for (int temp2 = 0; temp2 < feture[col].feturenum; temp2++)
    {
        if (class[temp2].classnum > classmax)
        {
            classmax = class[temp2].classnum;
            classname = class[temp2].classname;
        }
    }
    // 返回投票结果最多的类别
    return classname;
}
